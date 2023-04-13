//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "PassiveQueue.h"
#include "Job.h"
#include "IServer.h"

namespace queueing {


Define_Module(PassiveQueue);

PassiveQueue::PassiveQueue()
{
    selectionStrategy = nullptr;
}

PassiveQueue::~PassiveQueue()
{
    delete selectionStrategy;
}

void PassiveQueue::initialize()
{

    expiredSignal = registerSignal("expired");
    waitingTimeSignal = registerSignal("waiting_time");
    expiredJobs = 0;
    WATCH(expiredJobs);

    capacity = par("capacity");
    queue.setName("queue");
    fifo = par("fifo");

    jobsCounter = 0;
    noJobsLeft = new cMessage("noJobsLeft");
    noJobsLeft->addPar("PktLeft");
    noJobsLeft->par("PktLeft").setBoolValue(false);

    selectionStrategy = SelectionStrategy::create(par("sendingAlgorithm"), this, false);
    if (!selectionStrategy)
        throw cRuntimeError("invalid selection strategy");
}

void PassiveQueue::handleMessage(cMessage *msg)
{

        Job *job = check_and_cast<Job *>(msg);
        job->setTimestamp();

        int k = selectionStrategy->select();
        if (k < 0) {
            // enqueue if no idle server found
            queue.insert(job);
        }
        else if(length() == 0){

            simtime_t totalQueueingTime = simTime() - job->getTimestamp();

            job->setTotalQueueingTime(totalQueueingTime);
            emit(waitingTimeSignal,job->getTotalQueueingTime());

            // send through without queueing
            sendJob(job, k);
        }else
            throw cRuntimeError("This should not happen. Queue is NOT empty and there is an IDLE server attached to us.");

}

void PassiveQueue::refreshDisplay() const
{
    // change the icon color
    getDisplayString().setTagArg("i", 1, queue.isEmpty() ? "" : "cyan");
}

int PassiveQueue::length()
{
    return queue.getLength();
}

void PassiveQueue::request(int gateIndex)
{
    Enter_Method("request()!");
    ASSERT(!queue.isEmpty());

    Job *job;

    jobsCounter = queue.getLength();

    cGate *out1 = gate("out", gateIndex);

    int jobSent = 0;
    while((jobSent < 1) && (jobsCounter > 0) ){
        job = (Job*)queue.get(0);
        if(simTime() > job->getDeadlineTime()){

            if (hasGUI()){
                bubble("Expired!");
            }
            queue.remove(job);
            jobsCounter -= 1;
            expiredJobs++;
            std::cout << "jobs expired: " << expiredJobs << std::endl;
            emit(expiredSignal, 1);

        }else{

            jobSent = 1;
            jobsCounter -= 1;
            queue.remove(job);

            simtime_t totalQueueingTime = simTime() - job->getTimestamp();
            job->setTotalQueueingTime(totalQueueingTime);
            emit(waitingTimeSignal,job->getTotalQueueingTime());

            sendJob(job, gateIndex);
        }
    }

    noJobsLeft = new cMessage("noJobsLeft");
    noJobsLeft->addPar("PktLeft");
    send(noJobsLeft, out1);
}


void PassiveQueue::sendJob(Job *job, int gateIndex)
{
    cGate *out = gate("out", gateIndex);
    send(job, out);
    check_and_cast<IServer *>(out->getPathEndGate()->getOwnerModule())->allocate();
}

void PassiveQueue::finish() {
}



}; //namespace

