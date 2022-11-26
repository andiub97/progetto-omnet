////
//// This file is part of an OMNeT++/OMNEST simulation example.
////
//// Copyright (C) 2006-2015 OpenSim Ltd.
////
//// This file is distributed WITHOUT ANY WARRANTY. See the file
//// `license' for details on this and other legal matters.
////
//
//#include "Server.h"
//#include "Job.h"
//#include "SelectionStrategies.h"
//#include "IPassiveQueue.h"
//
//namespace queueing {
//
//Define_Module(Server);
//
//Server::Server()
//{
//    selectionStrategy = nullptr;
//    jobServiced = nullptr;
//    endServiceMsg = nullptr;
//    noPktMsg = nullptr;
////    endProducingMsgU1 = nullptr;
////    endProducingMsgU2 = nullptr;
//    allocated = false;
////    inventoriedPSU1 = 0;
////    inventoriedPSU2 = 0;
//}
//
//Server::~Server()
//{
//    delete selectionStrategy;
//    delete jobServiced;
//    cancelAndDelete(endServiceMsg);
////    cancelAndDelete(endProducingMsgU1);
////    cancelAndDelete(endProducingMsgU2);
//}
//
//void Server::initialize()
//{
//    busySignal = registerSignal("busy");
//    emit(busySignal, false);
//
//    endServiceMsg = new cMessage("end-service");
////    endProducingMsgU1 = new cMessage("end-producing-u1");
////    endProducingMsgU2 = new cMessage("end-producing-u2");
//    jobServiced = nullptr;
//    allocated = false;
//    selectionStrategy = SelectionStrategy::create(par("fetchingAlgorithm"), this, true);
//    if (!selectionStrategy)
//        throw cRuntimeError("invalid selection strategy");
//}
//
//void Server::handleMessage(cMessage *msg)
//{
//    if (msg == endServiceMsg) {
//        ASSERT(jobServiced != nullptr);
//        ASSERT(allocated);
//        simtime_t d = simTime() - endServiceMsg->getSendingTime();
//        jobServiced->setTotalServiceTime(jobServiced->getTotalServiceTime() + d);
//
//        EV << "Finishing service of " << jobServiced->getName() << endl;
//        //Send out the job
//        send(jobServiced, "out");
//
//        jobServiced = nullptr;
//        EV << "Lock access to PS (allocate) " << endl;
//
//        //this->startProducing();
//
//        //if (ev.isGUI()) getDisplayString().setTagArg("i",1,"");
//
//        // examine all input queues, and request a new job from a non empty queue
//        int k = selectionStrategy->select();
//        if (k >= 0){
//            EV << "requesting job from queue " << k << endl;
//            cGate *gate = selectionStrategy->selectableGate(k);
//            check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex());
//
//        }else if(msg == noPktMsg){
//            EV << "requesting job from queue " << k+1 << endl;
//            cGate *gate = selectionStrategy->selectableGate(k+1);
//            check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex());
//}
//
//
//
//    }
//
//
//    else
//    {
//        if (!allocated)
//            error("job arrived, but the sender did not call allocate() previously");
//
//        if (jobServiced)
//            error("job arrived while already servicing one");
//
//
//        jobServiced = check_and_cast<Job *>(msg);
//        simtime_t serviceTime = jobServiced->getService();
//        scheduleAt(simTime()+serviceTime, endServiceMsg);
//        emit(busySignal, true);
//
//    }
//}
//
////    }
////    else if (msg == endProducingMsgU1){
////        inventoriedPSU1++;
////        EV << "Finished producing PS for inventory U1: n="<< inventoriedPSU1 << endl;
////        this->startProducing();
////    }
////    else if (msg == endProducingMsgU2){
////        inventoriedPSU2++;
////        EV << "Finished producing PS for inventory U2: n="<< inventoriedPSU2 << endl;
////        this->startProducing();
////    }
////    else {
////        cancelEvent(endProducingMsgU1);
////        cancelEvent(endProducingMsgU2);
////        if (!allocated)
////            error("job arrived, but the sender did not call allocate() previously");
////        if (jobServiced)
////            throw cRuntimeError("a new job arrived while already servicing one");
////
////        jobServiced = check_and_cast<Job *>(msg);
//        //setting entryTime in the system for statistics
////        jobServiced->setEntryTime(simTime());
////        EV << "Starting service of " << jobServiced->getName() << endl;
//
//        //Serve job from inventory or directly
////        EV << "Job Type: " << jobServiced->getKind() << endl;
//
//
//
////        if (jobServiced->getKind() == 1) {
////            if(inventoriedPSU1>0){
////                EV << "Serving from inventory" << endl;
////                inventoriedPSU1--;
////                scheduleAt(simTime(),endServiceMsg);
////            } else {
////                simtime_t serviceTime = par("serviceTimeDirectU1");
////                scheduleAt(simTime()+serviceTime, endServiceMsg);
////            }
////        } else if (jobServiced->getKind() == 2) {
////            if(inventoriedPSU2>0){
////                EV << "Serving from inventory" << endl;
////                inventoriedPSU2--;
////                scheduleAt(simTime(),endServiceMsg);
////            } else {
////                simtime_t serviceTime = par("serviceTimeDirectU2");
////                scheduleAt(simTime()+serviceTime, endServiceMsg);
////            }
////        }
//
//        //emit(busySignal, true);
//    //}
////}
//
//void Server::startProducing(){
////    if(bernoulli(par("probabilityProducing").doubleValue())){
////        if(inventoriedPSU1+inventoriedPSU2 < par("maxInventoriedPS").intValue()) {
////            EV << "Start producing PS for U1: n="<< inventoriedPSU1 << endl;
////            simtime_t serviceTimeForInventory = par("serviceTimeForInventoryU1");
////            scheduleAt(simTime()+serviceTimeForInventory,endProducingMsgU1);
////        }
////    } else {
////        if(inventoriedPSU1+inventoriedPSU2 < par("maxInventoriedPS").intValue()) {
////            EV << "Start producing PS for U2: n="<< inventoriedPSU2 << endl;
////            simtime_t serviceTimeForInventory = par("serviceTimeForInventoryU2");
////            scheduleAt(simTime()+serviceTimeForInventory,endProducingMsgU2);
////        }
////    }
//}
//
//void Server::refreshDisplay() const
//{
//    getDisplayString().setTagArg("i2", 0, jobServiced ? "status/execute" : "");
//}
//
//void Server::finish()
//{
//}
//
//bool Server::isIdle()
//{
//    return !allocated;  // we are idle if nobody has allocated us for processing
//}
//
//void Server::allocate()
//{
//    allocated = true;
//}
//
//void Server::deallocate()
//{
//
//    allocated = false;
//    emit(busySignal, false);
//    // examine all input queues, and request a new job from a non empty queue
//    int k = selectionStrategy->select();
//    EV << "requesting job from queue " << k << endl;
//    if (k >= 0) {
//        EV << "requesting job from queue " << k << endl;
//        cGate *gate = selectionStrategy->selectableGate(k);
//        check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex());
//    }
//}
//
//}; //namespace
//


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
//    endProducingMsgU1 = nullptr;
//    endProducingMsgU2 = nullptr;
    allocated = false;
//    inventoriedPSU1 = 0;

//    inventoriedPSU2 = 0;

}

Server::~Server()
{
    delete selectionStrategy;
    delete jobServiced;
    cancelAndDelete(endServiceMsg);
//    cancelAndDelete(endProducingMsgU1);

//    cancelAndDelete(endProducingMsgU2);
}

void Server::initialize()
{
    busySignal = registerSignal("busy");
    emit(busySignal, false);

    endServiceMsg = new cMessage("end-service");

    noJobsLeft = new cMessage("noJobsLeft");

    service_time = par("service_time");
    deadline = par("deadline");
    gate= nullptr;
    gateIN=nullptr;

//    endProducingMsgU1 = new cMessage("end-producing-u1");
//    endProducingMsgU2 = new cMessage("end-producing-u2");

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
//        simtime_t d = simTime() - endServiceMsg->getSendingTime();
//        jobServiced->setTotalServiceTime(jobServiced->getTotalServiceTime() + d);

        if(jobServiced == nullptr){

        }else{
            EV << "Finishing service of " << jobServiced->getName() << endl;
            send(jobServiced, "out");

        }

        jobServiced = nullptr;
        EV << "Lock access to PS (allocate) " << endl;

        if(gateIN == nullptr){

            int k = selectionStrategy->select();
            if (k >= 0)
            {
                EV << "requesting job from queue " << k << endl;

                gate = selectionStrategy->selectableGate(k);
                EV << "requesting job from queue " << gate->getBaseId() << endl;
                gateIN = gate;
                check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex(), par("service_time"), par("deadline"));
            }
            //this->startProducing();
        }else{

            check_and_cast<IPassiveQueue *>(gateIN->getOwnerModule())->reqUntilPktsEnd(gateIN->getIndex());
        }
        scheduleAt(simTime()+par("service_time"), endServiceMsg);

    }
    else if(msg->hasPar("PktLeft")){
        EV << "print";
        gateIN = nullptr;
        cancelEvent(endServiceMsg);
        if(jobServiced == nullptr){
            scheduleAt(simTime(), endServiceMsg);
        }else{
            scheduleAt(simTime()+jobServiced->getServiceTime(),endServiceMsg);
        }

    }

//    else if (msg == endProducingMsgU1){

//        inventoriedPSU1++;
//        EV << "Finished producing PS for inventory U1: n="<< inventoriedPSU1 << endl;
//        this->startProducing();
//    }
//    else if (msg == endProducingMsgU2){
//        inventoriedPSU2++;
//        EV << "Finished producing PS for inventory U2: n="<< inventoriedPSU2 << endl;
//        this->startProducing();
//    }
    else {
//        cancelEvent(endProducingMsgU1);
//        cancelEvent(endProducingMsgU2);
        cancelEvent(endServiceMsg);

        if (!allocated){
            error("job arrived, but the sender did not call allocate() previously");
        }

        if (jobServiced)
            throw cRuntimeError("a new job arrived while already servicing one");

        jobServiced = check_and_cast<Job*>(msg);

        //setting entryTime in the system for statistics
        jobServiced->setEntryTime(simTime());
        EV << "Starting service of " << jobServiced->getName() << endl;

        int k = selectionStrategy->select();
        if (k < 0){

            scheduleAt(simTime()+par("service_time"), endServiceMsg);
        }else{

            scheduleAt(simTime()+jobServiced->getServiceTime(), endServiceMsg);
        }
//
//        if (jobServiced->getKind() == 1) {

//            if(inventoriedPSU1>0){
//                EV << "Serving from inventory" << endl;
//                inventoriedPSU1--;
//                scheduleAt(simTime(),endServiceMsg);
//            } else {
//                simtime_t serviceTime = par("serviceTimeDirectU1");
//                scheduleAt(simTime()+serviceTime, endServiceMsg);
//            }
//        } else if (jobServiced->getKind() == 2) {
//            if(inventoriedPSU2>0){
//                EV << "Serving from inventory" << endl;
//                inventoriedPSU2--;
//                scheduleAt(simTime(),endServiceMsg);
//            } else {
//                simtime_t serviceTime = par("serviceTimeDirectU2");
//                scheduleAt(simTime()+serviceTime, endServiceMsg);
//            }
//        }

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
        check_and_cast<IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex(), service_time, deadline);
    }
}

}; //namespace
