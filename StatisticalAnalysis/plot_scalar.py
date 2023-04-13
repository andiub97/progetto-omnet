import pandas as pd
import scipy.stats as st
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator

import json
import os
import math
import logging

pd.set_option('display.width', 200)
pd.set_option('display.max_columns', 10)

t95 = 2.093
t90 = 1.729
runs = 20


# Creating CSV and DataFrame
def create_csv_mean(DATA, log_level):
    logging.basicConfig(format='%(message)s', level=log_level)
    data = []
    for config in [directory for directory in os.listdir(DATA)]:
        config_dir = DATA + '/' + config
        logging.debug(config)
        for file in os.listdir(config_dir):
            file = config_dir + '/' + file
            N = config.replace('First-n', '').replace('Second-n', '').replace('Third-n', '').replace('Fourth-n', '').replace('Fifth-n', '').replace('Sixth-n', '').replace('Seventh-n', '').replace('Eighth-n', '')
            logging.debug('\t' + N + ' - ' + file.replace('.csv', ''))
            if 'Mean' in file:
                csv_file = pd.read_csv(file)
                name = csv_file['name'][0].replace(':mean', '')
                mean = csv_file['value'].mean()
                logging.debug('\t\tMean: ' + str(mean))
                std_dev = csv_file['value'].std()
                logging.debug('\t\tStdDev: ' + str(std_dev))
                var = csv_file['value'].var()
                logging.debug('\t\tVar: ' + str(var))
                std_err = std_dev / (math.sqrt(runs))
                logging.debug('\t\tStdErr:' + str(std_err))
                min_95 = mean - (t95 * math.sqrt(var) / math.sqrt(runs))
                max_95 = mean + (t95 * math.sqrt(var) / math.sqrt(runs))
                logging.debug("\t\tMin t95 ConfInt: " + str(min_95) + ' - Max t95 ConfInt: ' + str(max_95))
                min_90 = mean - (t90 * math.sqrt(var) / math.sqrt(runs))
                max_90 = mean + (t90 * math.sqrt(var) / math.sqrt(runs))
                logging.debug("\t\tMin t90 ConfInt: " + str(min_90) + ' - Max t90 ConfInt: ' + str(max_90))
                data.append([config, name, N, round(mean, 3), round(std_dev, 3), round(var, 3), round(std_err, 3),
                             round(min_95, 3), round(max_95, 3), round(min_90, 3), round(max_90, 3)])
    df_data = pd.DataFrame(data)
    df_data.columns = ['Config', 'Name', 'N', 'Mean', 'Std Dev', 'Var', 'Std Err', 'Min ConfInt t95', 'Max ConfInt t95',
                       'Min ConfInt t90', 'Max ConfInt t90']
    
    df_data = df_data.sort_values(by=['Config', 'Name'], ascending=True)
    logging.debug(df_data)

    df_data.to_csv('../scalar-results/Total_Data_Mean.csv', index=False)
    logging.info('CSV MEAN CREATED ' + DATA.replace('./', ''))
    return df_data


def create_csv_lifetime(DATA, log_level):
    logging.basicConfig(format='%(message)s', level=log_level)
    data = []
    for config in [directory for directory in os.listdir(DATA)]:
        config_dir = DATA + '/' + config
        logging.debug(config)
        for file in os.listdir(config_dir):
            file = config_dir + '/' + file
            N = config.replace('First-n', '').replace('Second-n', '').replace('Third-n', '').replace('Fourth-n', '').replace('Fifth-n', '').replace('Sixth-n', '').replace('Seventh-n', '').replace('Eighth-n', '')
            logging.debug('\t' + N + ' - ' + file.replace('.csv', ''))
            if 'LifeTime' in file:
                csv_file = pd.read_csv(file)
                name = csv_file['name'][0]
                mean = csv_file['value'].mean()
                logging.debug('\t\tMean: ' + str(mean))
                std_dev = csv_file['value'].std()
                logging.debug('\t\tStdDev: ' + str(std_dev))
                var = csv_file['value'].var()
                logging.debug('\t\tVar: ' + str(var))
                std_err = std_dev / (math.sqrt(runs))
                logging.debug('\t\tStdErr:' + str(std_err))
                min_95 = mean - (t95 * math.sqrt(var) / math.sqrt(runs))
                max_95 = mean + (t95 * math.sqrt(var) / math.sqrt(runs))
                logging.debug("\t\tMin t95 ConfInt: " + str(min_95) + ' - Max t95 ConfInt: ' + str(max_95))
                min_90 = mean - (t90 * math.sqrt(var) / math.sqrt(runs))
                max_90 = mean + (t90 * math.sqrt(var) / math.sqrt(runs))
                logging.debug("\t\tMin t90 ConfInt: " + str(min_90) + ' - Max t90 ConfInt: ' + str(max_90))
                data.append([config, name, N, round(mean, 3), round(std_dev, 3), round(var, 3), round(std_err, 3),
                             round(min_95, 3), round(max_95, 3), round(min_90, 3), round(max_90, 3)])
    df_data = pd.DataFrame(data)
    df_data.columns = ['Config', 'Name', 'N', 'Mean', 'Std Dev', 'Var', 'Std Err', 'Min ConfInt t95', 'Max ConfInt t95',
                       'Min ConfInt t90', 'Max ConfInt t90']

    df_data = df_data.sort_values(by=['Config', 'Name'], ascending=True)
    logging.debug(df_data)

    df_data.to_csv('../scalar-results/Total_Data_LifeTime.csv', index=False)
    logging.info('CSV LIFETIME CREATED ' + DATA.replace('./', ''))
    return df_data


def create_csv_expired_jobs(DATA, log_level):
    logging.basicConfig(format='%(message)s', level=log_level)
    data = []
    for config in [directory for directory in os.listdir(DATA)]:
        config_dir = DATA + '/' + config
        logging.debug(config)
        for file in os.listdir(config_dir):
            file = config_dir + '/' + file
            N = config.replace('First-n', '').replace('Second-n', '').replace('Third-n', '').replace('Fourth-n', '').replace('Fifth-n', '').replace('Sixth-n', '').replace('Seventh-n', '').replace('Eighth-n', '')
            logging.debug('\t' + N + ' - ' + file.replace('.csv', ''))
            if 'ExpJobs.csv' in file:
                csv_file = pd.read_csv(file)
                name = csv_file['name'][0]
                mean = csv_file['value'].mean()
                logging.debug('\t\tMean: ' + str(mean))
                std_dev = csv_file['value'].std()
                logging.debug('\t\tStdDev: ' + str(std_dev))
                var = csv_file['value'].var()
                logging.debug('\t\tVar: ' + str(var))
                std_err = std_dev / (math.sqrt(runs))
                logging.debug('\t\tStdErr:' + str(std_err))
                min_95 = mean - (t95 * math.sqrt(var) / math.sqrt(runs))
                max_95 = mean + (t95 * math.sqrt(var) / math.sqrt(runs))
                logging.debug("\t\tMin t95 ConfInt: " + str(min_95) + ' - Max t95 ConfInt: ' + str(max_95))
                min_90 = mean - (t90 * math.sqrt(var) / math.sqrt(runs))
                max_90 = mean + (t90 * math.sqrt(var) / math.sqrt(runs))
                logging.debug("\t\tMin t90 ConfInt: " + str(min_90) + ' - Max t90 ConfInt: ' + str(max_90))
                data.append([config, name, N, round(mean, 3), round(std_dev, 3), round(var, 3), round(std_err, 3),
                                round(min_95, 3), round(max_95, 3), round(min_90, 3), round(max_90, 3)])
    df_data = pd.DataFrame(data)
    df_data.columns = ['Config', 'Name', 'N', 'Mean', 'Std Dev', 'Var', 'Std Err', 'Min ConfInt t95', 'Max ConfInt t95',
                       'Min ConfInt t90', 'Max ConfInt t90']

    df_data = df_data.sort_values(by=['Config', 'Name'], ascending=True)
    logging.debug(df_data)

    df_data.to_csv('../scalar-results/Total_Data_Expired_Jobs.csv', index=False)
    logging.info('CSV EXPIRED_JOSB CREATED ' + DATA.replace('./', ''))
    return df_data


def create_csv_response_time(DATA_HISTOGRAM_DIR, log_level):
    logging.basicConfig(format='%(message)s', level=log_level)
    for config in [directory for directory in os.listdir(DATA_HISTOGRAM_DIR)]:
        config_dir = DATA_HISTOGRAM_DIR + '/' + config
        data=[]
        for jsons in (os.listdir(config_dir)):
            if 'ResponseTimeTotal.json' in jsons:
                print("\t" + config_dir + "/" + jsons)
                with open(config_dir + "/" + jsons) as file:
                    pointed_file = json.load(file)
                    for k in pointed_file.keys():
                        
                        
                        binedges=pointed_file[k]["histograms"][0]["binedges"]                   
                        binvalues=pointed_file[k]["histograms"][0]["binvalues"]
                        h = np.histogram(a=binedges[:-1],bins=binedges, weights=binvalues, density=True)                    
                        hist_dist=st.rv_histogram(h, density=True)
                        data.append([k, hist_dist.median()])

                    df_data = pd.DataFrame(data)
                    df_data.columns = ['Config', 'Value']
                    df_data.to_csv('../scalar/single-results/'+config+'/ResponseTimeTotal.csv', index=False)
                    data=[]  


def create_response_time_stats(DATA, log_level):
    logging.basicConfig(format='%(message)s', level=log_level)
    data = []
    for config in [directory for directory in os.listdir(DATA)]:
        config_dir = DATA + '/' + config
        logging.debug(config)
        for file in os.listdir(config_dir):
            N = config.replace('First-n', '').replace('Second-n', '').replace('Third-n', '').replace('Fourth-n', '').replace('Fifth-n', '').replace('Sixth-n', '').replace('Seventh-n', '').replace('Eighth-n', '')
            file = config_dir + '/' + file
            if 'ResponseTimeTotal.csv' in file:

                csv_file = pd.read_csv(file)
                mean=csv_file['Value'].mean()
                logging.debug('\t\tMean: ' + str(mean))
                std_dev = csv_file['Value'].std()
                logging.debug('\t\tStdDev: ' + str(std_dev))
                var = csv_file['Value'].var()
                logging.debug('\t\tVar: ' + str(var))
                std_err = std_dev / (math.sqrt(runs))
                logging.debug('\t\tStdErr:' + str(std_err))
                min_95 = mean - (t95 * math.sqrt(var) / math.sqrt(runs))
                max_95 = mean + (t95 * math.sqrt(var) / math.sqrt(runs))
                logging.debug("\t\tMin t95 ConfInt: " + str(min_95) + ' - Max t95 ConfInt: ' + str(max_95))
                min_90 = mean - (t90 * math.sqrt(var) / math.sqrt(runs))
                max_90 = mean + (t90 * math.sqrt(var) / math.sqrt(runs))
                logging.debug("\t\tMin t90 ConfInt: " + str(min_90) + ' - Max t90 ConfInt: ' + str(max_90))
                data.append([config, 'responseTime', N, round(mean, 3), round(std_dev, 3), round(var, 3), round(std_err, 3),
                            round(min_95, 3), round(max_95, 3), round(min_90, 3), round(max_90, 3)])
                print("----------------------------------------------------------")
    df_data = pd.DataFrame(data)
    df_data.columns = ['Config', 'Name', 'N', 'Mean', 'Std Dev', 'Var', 'Std Err', 'Min ConfInt t95', 'Max ConfInt t95',
                       'Min ConfInt t90', 'Max ConfInt t90']
    df_data.to_csv('../scalar-results/Total_Median_Response_Time.csv', index=False)
    logging.info('CSV MEDIAN OF RESPONSE PROBABILITY DISTRIBUTION CREATED ' + DATA.replace('./', ''))
    return df_data


# def create_plot_waiting_time(DATA_HISTOGRAM_DIR, log_level):
#     logging.basicConfig(format='%(message)s', level=log_level)
#     for config in [directory for directory in os.listdir(DATA_HISTOGRAM_DIR)]:
#         config_dir = DATA_HISTOGRAM_DIR + '/' + config
#         data=[]
#         for jsons in (os.listdir(config_dir)):
#             if 'WaitingTimeTotal.json' in jsons:
#                 print("\t" + config_dir + "/" + jsons)
#                 with open(config_dir + "/" + jsons) as file:
#                     pointed_file = json.load(file)

#                     fig, graph = plt.subplots()
#                     config=''
#                     num_queues=''
#                     for k in pointed_file.keys():

#                         config=k[0:9]
#                         num_queues=pointed_file[k]["histograms"][0]['module'][-1]
#                         binedges=pointed_file[k]["histograms"][0]["binedges"]                   
#                         binvalues=pointed_file[k]["histograms"][0]["binvalues"]
#                         h = np.histogram(a=binedges[:-1],bins=binedges, weights=binvalues, density=True)                    
#                         graph.plot(binedges, np.append(binvalues, 0), drawstyle='steps-post')   # or maybe steps-mid, for integers

#                     graph.autoscale_view()
#                     plt.savefig('./charts/charts_results/WaitingTime/'+ config+'-'+num_queues)
                                  


def create_plot_conf(df, DATA, log_level):
    logging.basicConfig(format='%(message)s', level=log_level)
    life_time = df[df['Name'].isin({'lifeTime'})]
    
    print(life_time)
    # Plot Parameters
    N = 3
    width = 0.25
    configuration = ['First', 'Second','Third','Fourth','Fifth','Sixth','Seventh','Eighth']

    for c in configuration:
        print(c)
        sub_df = df.loc[df['Config'].str.startswith(c).copy()]
        sub_df=sub_df.sort_values('N')

        fig_95, ax = plt.subplots()
        ind = np.arange(N)
        n=0
        low_bound_95 = ax.bar(ind + width, sub_df['Min ConfInt t95'][n:n + 3], width, bottom=0)
        mean = ax.bar(ind + 2 * width, sub_df['Mean'][n:n + 3], width, bottom=0)
        high_bound_95 = ax.bar(ind + 3 * width, sub_df['Max ConfInt t95'][n:n + 3], width, bottom=0)
        space = ax.bar(ind + 4 * width, np.asarray([0., 0., 0.]), width, bottom=0)
        ax.set_title(c + ' Configuration - ' + 'LifeTime' + '_95')
        ax.set_xticks((ind + 3 * width / 2))
        ax.set_xticklabels(('1', '2', '4'))
        ax.legend((low_bound_95[0], mean[0], high_bound_95[0]), ('Low Bound 95', 'Mean', 'High Bound 95'))
        ax.autoscale_view()
        plt.savefig(DATA + '/LifeTime/ConfInt_95/' + c + "_lifetime" + '_95')

        fig_90, ax = plt.subplots()
        ind = np.arange(N)
        n=0
        low_bound_90 = ax.bar(ind + width, sub_df['Min ConfInt t90'][n:n + 3], width, bottom=0)
        mean = ax.bar(ind + 2 * width, sub_df['Mean'][n:n + 3], width, bottom=0)
        high_bound_90 = ax.bar(ind + 3 * width, sub_df['Max ConfInt t90'][n:n + 3], width, bottom=0)
        space = ax.bar(ind + 4 * width, np.asarray([0., 0., 0.]), width, bottom=0)
        ax.set_title(c + ' Configuration - ' + 'LifeTime' + '_90')
        ax.set_xticks((ind + 3 * width / 2))
        ax.set_xticklabels(('1', '2', '4'))
        ax.legend((low_bound_90[0], mean[0], high_bound_90[0]), ('Low Bound 90', 'Mean', 'High Bound 90'))
        ax.autoscale_view()
        plt.savefig(DATA + '/LifeTime/ConfInt_90/' + c + "_lifetime" + '_90')

    logging.info('CHARTS CONF-INT CREATED ' + DATA)


def create_plot_lifetime(df, DATA, log_level):
    print("---------------------------------------------------------------------------")
    logging.basicConfig(format='%(message)s', level=log_level)

    # DataFrame per Name type
    life_time = df[df['Name'].isin({'lifeTime:mean', 'lifeTime:max', 'lifeTime:min'})]
    logging.info(life_time)
    
    # Plot Parameters
    N = [1, 2, 4]

    measure = life_time.iloc[0]['Name'].replace(':max', '').replace(':mean', '').replace(':min', '')
    for config in 'First','Second','Third','Fourth','Fifth','Sixth','Seventh','Eighth':
        fig_lifetime, ax = plt.subplots()
        maxs = []
        means = []
        mins = []
        for N_val in N:
            df_triplet = life_time[life_time['Config'].isin({config + '-n' + str(N_val)})]

            maxs.append(df_triplet.iloc[0]['Mean'])
            means.append(df_triplet.iloc[1]['Mean'])
            mins.append(df_triplet.iloc[2]['Mean'])

        max_plt = ax.plot(N, maxs)
        mean_plt = ax.plot(N, means)
        min_plt = ax.plot(N, mins)
        ax.set_title(config + ' Configuration - ' + measure)
        ax.legend((max_plt[0], mean_plt[0], min_plt[0]), ('Max LifeTime', 'Mean LifeTime', 'Min LifeTime'))
        ax.autoscale_view()
        plt.xticks([1,2,4], N)
        plt.savefig(DATA + '/LifeTime/' + config + '_' + measure)
        plt.show()
    logging.info('CHARTS LIFETIME CREATED ' + DATA)


def create_plot_expired_jobs(df, DATA, log_level):
    logging.basicConfig(format='%(message)s', level=log_level)

    # DataFrame per Name type
    expired_sum = df[df['Name'].isin({'expired:count'})]

    # Plot Parameters
    N = [1,2,4]

    measure = expired_sum.iloc[0]['Name'].replace(':count', '')
    for config in 'First','Second','Third','Fourth','Fifth','Sixth','Seventh','Eighth':

        expired_jobs = []
        mins_95=[]
        maxs_95=[]
        mins_90=[]
        maxs_90=[]
        
        for N_val in N:
            
            df_i = expired_sum[expired_sum['Config'].isin({config + '-n' + str(N_val)})]
            expired_jobs.append(round(df_i.iloc[0]['Mean']+df_i.iloc[1]['Mean']+df_i.iloc[2]['Mean']+df_i.iloc[3]['Mean']))
            
            maxs_90 = [df_i.iloc[i]['Max ConfInt t90'] for i in [0,1,2,3]]
            mins_90 = [df_i.iloc[i]['Min ConfInt t90'] for i in [0,1,2,3]]
            maxs_95 = [df_i.iloc[i]['Max ConfInt t95'] for i in [0,1,2,3]]
            mins_95 = [df_i.iloc[i]['Min ConfInt t95'] for i in [0,1,2,3]]

            width = 0.25
            fig_95, ax = plt.subplots()
            ind = np.arange(4)
            n=0
            low_bound_95 = ax.bar(ind + width, mins_95[n:n + 4], width, bottom=0)
            high_bound_95 = ax.bar(ind + 2 * width, maxs_95[n:n + 4], width, bottom=0)
            space = ax.bar(ind + 4 * width, np.asarray([0., 0., 0., 0.]), width, bottom=0)
            ax.set_title(config +"-n" + str(N_val) + ' Configuration - ' + 'Expired' + '_95')
            ax.set_xticks((ind + 3 * width / 2))
            ax.set_xticklabels(('1', '2', '3','4'))
            ax.legend((low_bound_95[0], high_bound_95[0]), ('Low Bound 95', 'High Bound 95'))
            ax.autoscale_view()
            print("---------------")
            plt.savefig(DATA + '/ExpiredJobs/ConfInt_95/' + config + "-n" + str(N_val) + "_expired" + '_95')


            fig_90, ax = plt.subplots()
            ind = np.arange(4)
            n=0
            low_bound_90 = ax.bar(ind + width, mins_90[n:n + 4], width, bottom=0)
            high_bound_90 = ax.bar(ind + 2 * width, maxs_90[n:n + 4], width, bottom=0)
            space = ax.bar(ind + 4 * width, np.asarray([0., 0., 0., 0.]), width, bottom=0)
            ax.set_title(config +"-n" + str(N_val) + ' Configuration - ' + 'Expired' + '_90')
            ax.set_xticks((ind + 3 * width / 2))
            ax.set_xticklabels(('1', '2', '3','4'))
            ax.legend((low_bound_90[0], high_bound_90[0]), ('Low Bound 90', 'High Bound 90'))
            ax.autoscale_view()
            print("---------------")
            plt.savefig(DATA + '/ExpiredJobs/ConfInt_90/' + config + "-n" + str(N_val) + "_expired" + '_90')

        fig, ax = plt.subplots()
        ax.plot(N, expired_jobs)
        ax.set_title(config + ' Configuration - ' + measure + ' Mean')
        ax.autoscale_view()
        plt.xticks([1,2,4], N)
        plt.savefig(DATA + '/ExpiredJobs/' + config + '_' + measure + '_Mean')

        plt.cla()
        plt.clf()
        plt.close(fig)


    logging.info('CHARTS EXPIRED JOBS CREATED ' + DATA)


def create_plot_median_response_time(DATA, log_level):

    logging.basicConfig(format='%(message)s', level=log_level)
    
    # Plot Parameters
    N = 3
    width = 0.25
    configuration = ['First', 'Second', 'Third', 'Fourth','Fifth','Sixth','Seventh','Eighth']
    df = pd.read_csv('../scalar-results/Total_Median_Response_Time.csv')

    for c in configuration:
        print(c)
        sub_df = df.loc[df['Config'].str.startswith(c).copy()]        
        sub_df=sub_df.sort_values('N')

        fig_95, ax = plt.subplots()
        ind = np.arange(N)
        n=0
        low_bound_95 = ax.bar(ind + width, sub_df['Min ConfInt t95'][n:n + 3], width, bottom=0)
        mean = ax.bar(ind + 2 * width, sub_df['Mean'][n:n + 3], width, bottom=0)
        high_bound_95 = ax.bar(ind + 3 * width, sub_df['Max ConfInt t95'][n:n + 3], width, bottom=0)
        space = ax.bar(ind + 4 * width, np.asarray([0., 0., 0.]), width, bottom=0)
        ax.set_title(c + ' Configuration - ' + c + 'Response Time' + '_95')
        ax.set_xticks((ind + 3 * width / 2))
        ax.set_xticklabels(('1', '2', '4'))
        ax.legend((low_bound_95[0], mean[0], high_bound_95[0]), ('Low Bound 95', 'Mean', 'High Bound 95'))
        ax.autoscale_view()
        print("---------------")
        plt.savefig(DATA + '/ResponseTime/ConfInt_95/' + c + "_responsetime" + '_95')
        plt.show()

        fig_90, bx = plt.subplots()
        ind = np.arange(N)
        n=0
        low_bound_90 = bx.bar(ind + width, sub_df['Min ConfInt t90'][n:n + 3], width, bottom=0)
        mean_90 = bx.bar(ind + 2 * width, sub_df['Mean'][n:n + 3], width, bottom=0)
        high_bound_90 = bx.bar(ind + 3 * width, sub_df['Max ConfInt t90'][n:n + 3], width, bottom=0)
        space = bx.bar(ind + 4 * width, np.asarray([0., 0., 0.]), width, bottom=0)
        bx.set_title(c + ' Configuration - ' + c + 'Response Time' + '_90')
        bx.set_xticks((ind + 3 * width / 2))
        bx.set_xticklabels(('1', '2', '4'))
        bx.legend((low_bound_90[0], mean_90[0], high_bound_90[0]), ('Low Bound 90', 'Mean', 'High Bound 90'))
        bx.autoscale_view()
        plt.savefig(DATA + '/ResponseTime/ConfInt_90/' + c + '_responsetime' + '_90')
        plt.show()

    logging.info('CHARTS MEDIAN OF RESPONSE PROBABILITY DISTRIBUTION CREATED ' + DATA)
    return 0

if __name__ == "__main__":
    # Extract data results with transient
    df_data_mean = create_csv_mean('../scalar/single-results', logging.INFO)
    df_data_lifetime = create_csv_lifetime('../scalar/single-results', logging.INFO)
    df_data_expJobs = create_csv_expired_jobs('../scalar/single-results', logging.INFO)
    df_median_response_time = create_csv_response_time('../scalar/single-results', logging.INFO)
    df_total_median_response_time = create_response_time_stats('../scalar/single-results', logging.INFO)
    
    # create_plot_waiting_time('../scalar/single-results',logging.INFO)
    create_plot_conf(df_data_mean, './charts/charts_results', logging.INFO)
    create_plot_lifetime(df_data_lifetime, './charts/charts_results', logging.INFO)
    create_plot_expired_jobs(df_data_expJobs, './charts/charts_results', logging.INFO)
    create_plot_median_response_time('./charts/charts_results', logging.INFO)