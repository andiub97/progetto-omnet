//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "Server.h"
#include "Job.h"
#include "SelectionStrategies.h"
#include "IPassiveQueue.h"

namespace queueing {

Define_Module(Server);

Server::Server()
{
    selectionStrategy = nullptr;
    jobServiced = nullptr;
    endServiceMsg = nullptr;
    noJobsLeft = nullptr;
    allocated = false;

}

Server::~Server()
{
    delete selectionStrategy;
    delete jobServiced;
    cancelAndDelete(endServiceMsg);
}

void Server::initialize()
{
    busySignal = registerSignal("busy");
    emit(busySignal, false);

    responseTimeSignal = registerSignal("response_time");

    endServiceMsg = new cMessage("end-service");
    noJobsLeft = new cMessage("noJobsLeft");

    visitQueueGate=nullptr;

    served_jobs = 0;
    jobServiced = nullptr;
    allocated = false;
    selectionStrategy = SelectionStrategy::create(par("fetchingAlgorithm"), this, true);
    if (!selectionStrategy)
        throw cRuntimeError("invalid selection strategy");

}

void Server::handleMessage(cMessage *msg)

{

    if (msg == endServiceMsg) {
        ASSERT(jobServiced != nullptr);
        ASSERT(allocated);

        if(jobServiced == nullptr){

        }else{
            EV << "Finishing service of " << jobServiced->getName() << endl;
            std::cout << "jobs served: " << served_jobs++ << std::endl;
            emit(responseTimeSignal,jobServiced->getTotalQueueingTime() + jobServiced->getTotalServiceTime());

            std::cout << "response time: " << jobServiced->getTotalQueueingTime() + jobServiced->getTotalServiceTime() << std::endl;
            send(jobServiced, "out");

        }

        jobServiced = nullptr;

        if(visitQueueGate == nullptr){

            int k = selectionStrategy->select();
            if (k >= 0)
            {
                EV << "requesting job from queue " << k << endl;

                visitQueueGate = selectionStrategy->selectableGate(k);
                EV << "requesting job from queue " << visitQueueGate->getBaseId() << endl;
                check_and_cast<IPassiveQueue *>(visitQueueGate->getOwnerModule())->request(visitQueueGate->getIndex());
                scheduleAt(simTime(), endServiceMsg);
            }
            else{
                cancelEvent(endServiceMsg);
                emit(busySignal, false);
                allocated = false;

            }
        }else{

            check_and_cast<IPassiveQueue *>(visitQueueGate->getOwnerModule())->request(visitQueueGate->getIndex());
            scheduleAt(simTime(), endServiceMsg);
        }

    }
    else if(msg->hasPar("PktLeft")){

        EV << "print";
        visitQueueGate = nullptr;

    }

    else {
        cancelEvent(endServiceMsg);

        if (!allocated){
            error("job arrived, but the sender did not call allocate() previously");
        }

        if (jobServiced)
            throw cRuntimeError("a new job arrived while already servicing one");

        jobServiced = check_and_cast<Job*>(msg);
        simtime_t service_time = jobServiced->getTotalServiceTime();
        //setting entryTime in the system for statistics
        jobServiced->setEntryTime(simTime());
        EV << "Starting service of " << jobServiced->getName() << endl;

        scheduleAt(simTime()+service_time, endServiceMsg);
        emit(busySignal, true);
    }
}


void Server::refreshDisplay() const
{
    getDisplayString().setTagArg("i2", 0, jobServiced ? "status/execute" : "");
}

void Server::finish()
{
}

bool Server::isIdle()
{
    return !allocated;  // we are idle if nobody has allocated us for processing
}

void Server::allocate()
{
    allocated = true;
}

void Server::deallocate()
{

    allocated = false;
    emit(busySignal, false);
    // examine all input queues, and request a new job from a non empty queue
    int k = selectionStrategy->select();
    EV << "requesting job from queue " << k << endl;
    if (k >= 0) {
        EV << "requesting job from queue " << k << endl;
        cGate *gate = selectionStrategy->selectableGate(k);
        check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex());
    }
}

}; //namespace
