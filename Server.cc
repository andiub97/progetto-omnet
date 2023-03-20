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

    endServiceMsg = new cMessage("end-service");
    noJobsLeft = new cMessage("noJobsLeft");

    queueGate= nullptr;
    visitQueueGate=nullptr;

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
            send(jobServiced, "out");

        }

        jobServiced = nullptr;

        if(visitQueueGate == nullptr){

            int k = selectionStrategy->select();
            if (k >= 0)
            {
                EV << "requesting job from queue " << k << endl;

                queueGate = selectionStrategy->selectableGate(k);
                EV << "requesting job from queue " << queueGate->getBaseId() << endl;
                visitQueueGate = queueGate;
                check_and_cast<IPassiveQueue *>(visitQueueGate->getOwnerModule())->request(visitQueueGate->getIndex());
                scheduleAt(simTime(), endServiceMsg);
                service_time = SimTime::ZERO;
            }else{
                cancelEvent(endServiceMsg);
                emit(busySignal, false);
                allocated = false;

                service_time = SimTime::ZERO;
            }
        }else{

            check_and_cast<IPassiveQueue *>(visitQueueGate->getOwnerModule())->request(visitQueueGate->getIndex());
            scheduleAt(simTime(), endServiceMsg);
            service_time = SimTime::ZERO;
        }

    }
    else if(msg->hasPar("PktLeft")){

        EV << "print";
        visitQueueGate = nullptr;
        cancelEvent(endServiceMsg);

        if(jobServiced == nullptr){
            scheduleAt(simTime(), endServiceMsg);
        }else{
            scheduleAt(simTime()+service_time,endServiceMsg);
        }

        service_time = SimTime::ZERO;
    }

    else {
        cancelEvent(endServiceMsg);

        if (!allocated){
            error("job arrived, but the sender did not call allocate() previously");
        }

        if (jobServiced)
            throw cRuntimeError("a new job arrived while already servicing one");

        jobServiced = check_and_cast<Job*>(msg);
        service_time = jobServiced->getTotalServiceTime();
        //setting entryTime in the system for statistics
        jobServiced->setEntryTime(simTime());
        EV << "Starting service of " << jobServiced->getName() << endl;

        int k = selectionStrategy->select();
        if (k < 0){

            scheduleAt(simTime()+service_time, endServiceMsg);
        }else{

            scheduleAt(simTime()+service_time, endServiceMsg);
        }
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
