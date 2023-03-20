//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package org.omnetpp.queueing;

network Progetto
{
    @display("bgb=604,302");
    submodules:
        source: Source {
            @display("p=36,152");
            //jobType = 1;
            //jobPriority = 1;
        }
        sink: Sink {
            @display("p=488,152");
        }
        server: Server {
            @display("p=384,152");
        }
        router: Router {
            @display("p=171,152");
        }
        passiveQueue1: PassiveQueue {
            @display("p=276,64");
        }
        passiveQueue2: PassiveQueue {
            @display("p=276,126");
        }
        passiveQueue3: PassiveQueue {
            @display("p=276,191");
        }
        passiveQueue4: PassiveQueue {
            @display("p=276,253");
        }
    connections:
        server.out --> sink.in++;
        source.out --> router.in++;
        router.out++ --> passiveQueue1.in++;
        router.out++ --> passiveQueue2.in++;
        router.out++ --> passiveQueue3.in++;
        router.out++ --> passiveQueue4.in++;
        passiveQueue1.out++ --> server.in++;
        passiveQueue2.out++ --> server.in++;
        passiveQueue3.out++ --> server.in++;
        passiveQueue4.out++ --> server.in++;
        server.out1++ --> passiveQueue1.in++;
        server.out1++ --> passiveQueue2.in++;
        server.out1++ --> passiveQueue3.in++;
        server.out1++ --> passiveQueue4.in++;
}
