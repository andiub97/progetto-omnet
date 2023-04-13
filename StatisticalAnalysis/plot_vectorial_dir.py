import numpy as np
import matplotlib.pyplot as plt
import scipy as scp

import json
import os
import sys


def mean_convergence(array):
    array = np.asarray(array)
    meaned = []
    meaned.append(array[0])
    for i in range(1, array.size):
        meaned.append(np.mean(array[:i]))
    return meaned


def plot_measure(dir_measure):
    DATA_VEC_DIR = "../vectorial"
    # DATA_VEC_DIR = "./data_vectorial_prova"
    for results_dir in os.listdir(DATA_VEC_DIR):
        RESULTS_DIR = DATA_VEC_DIR + "/" + results_dir + "/" + dir_measure
        print(RESULTS_DIR)
        for jsons in (os.listdir(RESULTS_DIR)):
            print("\t" + RESULTS_DIR + "/" + jsons)
            with open(RESULTS_DIR + "/" + jsons) as file:
                pointed_file = json.load(file)
                #vectors = pointed_file["vectors"]
                vectors = []
                for k in pointed_file.keys():

                    vectors = vectors + pointed_file[k]["vectors"]                        

                fig, graph = plt.subplots()
                for vector in vectors:
                    graph.plot(vector['time'],mean_convergence(vector['value']))
                    
                    graph.set_title(
                        pointed_file[k]['attributes']['configname'] + " - " + dir_measure 
                        +
                        '\n\nNum queues: ' + pointed_file[k]['config'][1]['**.numQueues'] + "\n" +
                        '     InterArrival: '   + pointed_file[k]['config'][2]['**.source.interArrivalTime'] + "\n" +
                        '     Service Time: '   + pointed_file[k]['config'][3]['**.source.service_time'] + "\n" +
                        '     Deadline Time: '  + pointed_file[k]['config'][4]['**.source.deadline']
                    )
                graph.autoscale_view()
                plt.savefig('./charts/charts_vector_results' +
                            "/" + dir_measure + "/" + jsons.replace('.json', ''), bbox_inches='tight')
                plt.clf()
                
        break


if __name__ == "__main__":
    plot_measure("lifeTime")
