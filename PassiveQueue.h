//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __QUEUEING_PASSIVE_QUEUE_H
#define __QUEUEING_PASSIVE_QUEUE_H

#include "QueueingDefs.h"
#include "IPassiveQueue.h"
#include "SelectionStrategies.h"
#include "Job.h"

namespace queueing {

class SelectionStrategy;

/**
 * A passive queue, designed to co-operate with IServer using method calls.
 */
class QUEUEING_API PassiveQueue : public cSimpleModule, public IPassiveQueue
{
    private:
        simsignal_t expiredSignal;
        int expiredJobs;

        bool fifo;
        int capacity;
        cQueue queue;
        SelectionStrategy *selectionStrategy;
        cMessage *noJobsLeft;

        long jobsCounter=0;

        void sendJob(Job *job, int gateIndex);


    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void refreshDisplay() const override;
        virtual void finish() override;

    public:
        PassiveQueue();
        virtual ~PassiveQueue();
        // The following methods are called from IServer:
        virtual int length() override;
        virtual void request(int gateIndex) override;

};

}; //namespace

#endif
