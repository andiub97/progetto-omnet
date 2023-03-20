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
// Destroys (or optionally keep) the packets and collects statistics
//
simple Sink	
{
    parameters:
        @group(Queueing);
        @display("i=block/sink");
        @signal[lifeTime](type="simtime_t");
        @statistic[lifeTime](title="lifetime of arrived jobs";unit=s;record=vector,mean,max,min;interpolationmode=none);
        bool keepJobs = false; // whether to keep the received jobs till the end of simulation
    gates:
        input in[];
}

