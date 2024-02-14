import pandas as pd
import matplotlib.pyplot as plt


def plot():
    # Read the setup.csv file
    fprs = ['001', '005', '010']
    for fpr in fprs:
        df = pd.read_csv('./results/openmp/'+fpr+'/setup.csv', sep=';')

        tests = [2, 4, 6, 8, 10, 12, 14, 16]
        # Plot execution times
        plt.figure()
        plt.title('Setup: Execution times')
        plt.plot(df['test'], df['tSeq'], '-o', label='Sequential')
        for i in tests:
            plt.plot(df['test'], df['tPar{}'.format(i)], '-o', label='{} Threads'.format(i))
        plt.xlabel('Selected emails')
        plt.ylabel('Time (s)')
        plt.tight_layout()
        plt.legend()
        plt.grid()
        plt.savefig('./results/openmp/'+str(fpr)+'/setup_times.png')

        # Plot speedup
        plt.figure()
        plt.title('Setup: Speedup')
        plt.plot(df['test'], df['tSeq']/df['tSeq'], '-o', label='Sequential')
        for i in tests:
            plt.plot(df['test'], df['speedUp{}'.format(i)], '-o', label='{} Threads'.format(i))
        plt.xlabel('Selected emails')
        plt.ylabel('Speedup')
        plt.legend()
        plt.tight_layout()
        plt.grid()
        plt.savefig('./results/openmp/'+str(fpr)+'/setup_speedup.png')

        # Plot FPR
        plt.figure()
        plt.title('Setup: False Positive Rate')
        plt.plot(df['test'], df['fpr'], '-o')
        plt.xlabel('Selected emails')
        plt.ylabel('FPR')
        plt.tight_layout()
        plt.legend()
        plt.grid()
        plt.savefig('./results/openmp/'+str(fpr)+'/setup_fpr.png')

        # Read the filter.csv file
        df = pd.read_csv('./results/openmp/'+str(fpr)+'/filter.csv', sep=';')

        tests = [2, 4, 6, 8, 10, 12, 14, 16]
        # Plot execution times Filter1
        plt.figure()
        plt.title('Filter1: Execution times')
        plt.plot(df['test'], df['tSeq'], '-o', label='Sequential')
        for i in tests:
            plt.plot(df['test'], df['tPar{}'.format(i)], '-o', label='{} Threads'.format(i))
        plt.xlabel('Selected emails')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid()
        plt.tight_layout()
        plt.savefig('./results/openmp/'+str(fpr)+'/filter1_times.png')

        # Plot speedup Filter1
        plt.figure()
        plt.title('Filter1: Speedup')
        plt.plot(df['test'], df['tSeq']/df['tSeq'], '-o', label='Sequential')
        for i in tests:
            plt.plot(df['test'], df['speedUp{}'.format(i)], '-o', label='{} Threads'.format(i))
        plt.xlabel('Selected emails')
        plt.ylabel('Speedup')
        plt.legend()
        plt.grid()
        plt.tight_layout()
        plt.savefig('./results/openmp/'+str(fpr)+'/filter1_speedup.png')

        plt.figure()
        plt.title('Filter2: Execution times')
        plt.plot(df['test'], df['tSeq'], '-o', label='Sequential')
        for i in tests:
            plt.plot(df['test'], df['tPar{}'.format(i)+'Type2'], '-o', label='{} Threads'.format(i))
        plt.xlabel('Selected emails')
        plt.ylabel('Time (s)')
        plt.legend()
        plt.grid()
        plt.tight_layout()
        plt.savefig('./results/openmp/'+str(fpr)+'/filter2_times.png')

        plt.figure()
        plt.title('Filter2: Speedup')
        plt.plot(df['test'], df['tSeq']/df['tSeq'], '-o', label='Sequential')
        for i in tests:
            plt.plot(df['test'], df['speedUp{}'.format(i)+'Type2'], '-o', label='{} Threads'.format(i))
        plt.xlabel('Selected emails')
        plt.ylabel('Speedup')
        plt.legend()
        plt.grid()
        plt.tight_layout()
        plt.savefig('./results/openmp/'+str(fpr)+'/filter2_speedup.png')

        # Plot FPR
        plt.figure()
        plt.title('Filter: False Positive Rate')
        plt.plot(df['test'], df['fpr'], '-o')
        plt.xlabel('Selected emails')
        plt.ylabel('FPR')
        plt.legend()
        plt.grid()
        plt.tight_layout()
        plt.savefig('./results/openmp/'+str(fpr)+'/filter_fpr.png')


if __name__ == '__main__':
    plot()
