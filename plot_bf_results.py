import pandas as pd
import matplotlib.pyplot as plt


def plot():
    # Read the setup.csv file
    df = pd.read_csv('./results/csv/setup.csv', sep=';')

    tests = [2, 4, 6, 8]
    # Plot execution times
    plt.figure()
    plt.plot(df['test'], df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['tPar{}'.format(i)], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Time (s)')
    plt.tight_layout()
    plt.legend()

    plt.figure()
    plt.plot(df['test'], df['tSeq']/df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['speedUp{}'.format(i)], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Speedup')
    plt.legend()
    plt.tight_layout()

    # Read the setup.csv file
    df = pd.read_csv('./results/csv/filter.csv', sep=';')

    tests = [2, 4, 6, 8]
    # Plot execution times
    plt.figure()
    plt.plot(df['test'], df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['tPar{}'.format(i)], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Time (s)')
    plt.legend()
    plt.tight_layout()

    plt.figure()
    plt.plot(df['test'], df['tSeq']/df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['speedUp{}'.format(i)], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Speedup')
    plt.legend()
    plt.tight_layout()

    plt.show()


if __name__ == '__main__':
    plot()
