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
    queueLengthSignal = registerSignal("queueLength");
    emit(queueLengthSignal, 0);

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

    // check for container capacity
    if (capacity >= 0 && queue.getLength() >= capacity) {
        EV << "Queue full! Job dropped.\n";
        if (hasGUI())
            bubble("Dropped!");
        //emit(droppedSignal, 1);
        delete msg;
        return;
    }

    int k = selectionStrategy->select();
    if (k < 0) {
        // enqueue if no idle server found
        queue.insert(job);
        emit(queueLengthSignal, length());
        job->setQueueCount(job->getQueueCount() + 1);
    }
    else if (length() == 0) {
        // send through without queueing
        sendJob(job, k);
    }
    else
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

void PassiveQueue::request(int gateIndex, simtime_t serviceTime, simtime_t deadline)
{
    Enter_Method("request()!");
    ASSERT(!queue.isEmpty());

    Job *job;
    if (fifo) {
        job = (Job *)queue.front();
    }
    else {
        job = (Job *)queue.back();
        // FIXME this may have bad performance as remove uses linear search
        queue.remove(job);
    }
    emit(queueLengthSignal, length());

    job->setQueueCount(job->getQueueCount()+1);
    simtime_t d = simTime() - job->getTimestamp();
    job->setTotalQueueingTime(job->getTotalQueueingTime() + d);
    //emit(queueingTimeSignal, d);

    jobsCounter = queue.getLength();

    for (int i = 0; i < queue.getLength(); i++){
        job = (Job *) queue.get(i);
        job->setServiceTime(serviceTime);
        job->setDeadline(simTime()+deadline);

    }

    job = (Job*)queue.get(0);

    cGate *out1 = gate("out", gateIndex);

    if(jobsCounter > 1){

        queue.remove(job);
        jobsCounter = jobsCounter - 1;
        sendJob(job, gateIndex);


    }else if (jobsCounter == 1){
        queue.remove(job);
        jobsCounter = jobsCounter - 1;
        sendJob(job, gateIndex);


        noJobsLeft = new cMessage("noJobsLeft");
        noJobsLeft->addPar("PktLeft");
        noJobsLeft->par("PktLeft").setBoolValue(false);
        send(noJobsLeft, out1);

    }else{

        noJobsLeft = new cMessage("noJobsLeft");
        noJobsLeft->addPar("PktLeft");
        noJobsLeft->par("PktLeft").setBoolValue(false);
        send(noJobsLeft, out1);
    }

}


void PassiveQueue::reqUntilPktsEnd(int gateIndex)
{
    Enter_Method("request()!");
    ASSERT(!queue.isEmpty());

    Job *job;
    if (fifo) {
        job = (Job *)queue.front();
    }
    else {
        job = (Job *)queue.back();
        // FIXME this may have bad performance as remove uses linear search
        queue.remove(job);
    }
    emit(queueLengthSignal, length());

    job->setQueueCount(job->getQueueCount()+1);
    simtime_t d = simTime() - job->getTimestamp();
    job->setTotalQueueingTime(job->getTotalQueueingTime() + d);
    //emit(queueingTimeSignal, d);

    cGate *out1 = gate("out", gateIndex);

    int dropped = 0;
    Job* j = (Job *) queue.front();
    int i=0;
    while ((i<jobsCounter) && (simTime() < j->getDeadline())){
        queue.remove(j);
        j = (Job*) queue.front();
        if (hasGUI())
            bubble("Expired!");
        dropped ++;
        i++;

    }

    jobsCounter -= dropped;


    if(jobsCounter > 1){
        queue.remove(job);
        jobsCounter = jobsCounter - 1;
        sendJob(job, gateIndex);


    }else if(jobsCounter == 1){
        queue.remove(job);
        jobsCounter = jobsCounter - 1;

        sendJob(job, gateIndex);


        noJobsLeft = new cMessage("noJobsLeft");
        noJobsLeft->addPar("PktLeft");
        noJobsLeft->par("PktLeft").setBoolValue(false);
        send(noJobsLeft, out1);

    }else{
        noJobsLeft = new cMessage("noJobsLeft");
        noJobsLeft->addPar("PktLeft");
        noJobsLeft->par("PktLeft").setBoolValue(false);
        send(noJobsLeft, out1);
    }


}


void PassiveQueue::sendJob(Job *job, int gateIndex)
{
    cGate *out = gate("out", gateIndex);
    send(job, out);
    check_and_cast<IServer *>(out->getPathEndGate()->getOwnerModule())->allocate();
}


//void PassiveQueue::sendJob1(Job *job, int gateIndex)
//{
//    cGate *out = gate("out", gateIndex);
//    for (int i = 0; i < queue.getLength(); i++){
//            job = (Job *)queue.pop();
//            send(job, out);
//        }
//    check_and_cast<IServer *>(out->getPathEndGate()->getOwnerModule())->allocate();
//}

}; //namespace

