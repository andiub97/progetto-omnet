//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

package org.omnetpp.queueing;

//
// Passive queue. Messages have to be requested via direct method call.
// Its output must be connected to a Server.
//
// @author rhornig
// @todo minDelay not implemented
//
simple PassiveQueue
{
    parameters:
        @group(Queueing);
        @signal[expired](type="long");
        @statistic[expired](title="expired job event";record=vector?,sum;interpolationmode=none);
        @display("i=block/passiveq;q=queue");

        int capacity = -1;  // negative capacity means unlimited queue
        bool fifo = true;   // whether the module works as a queue (fifo=true) or a stack (fifo=false)
        string sendingAlgorithm @enum("priority","random","roundRobin","minDelay") = "priority";
                                     // how the queue tries to find a suitable server for an incoming job
        
    gates:
        input in[];
        output out[];
}