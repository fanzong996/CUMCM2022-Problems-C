# encoding: utf-8
# environment：Anaconda 2.2.0 Python3.9
"""
#依赖库：
numpy                 1.19.3
pandas                1.3.3
sklearn                1.0.2
time	           default
os	           default
"""
import os

os.chdir('./data')#设置根目录

from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import MinMaxScaler
import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder
import time

def data_reader(csv_path):#读取CSV数据，生成dataloader
    df = pd.read_csv(csv_path)
    input_cols = list(df.columns)[1:-1]
    target_col = 'label'
    numeric_cols = df.select_dtypes(include=np.number).columns.tolist()[:-1]

    scaler = MinMaxScaler()
    scaler.fit(df[numeric_cols])
    df[numeric_cols] = scaler.transform(df[numeric_cols])
    le = LabelEncoder()

    target = df['label']
    df['label'] = le.fit_transform(target)
    test_size = 33

    train_df, test_df = train_test_split(df, test_size=test_size, random_state=None, shuffle=True)
    test_inputs = test_df[input_cols].copy()
    test_targets = test_df[target_col].copy()
    train_inputs = train_df[input_cols].copy()
    train_targets = train_df[target_col].copy()
    return (test_inputs, test_targets, train_inputs, train_targets)

def train_test_Module(data_load):#KNN训练与测试模块
    test_inputs, test_targets, train_inputs, train_targets = data_load
    start = time.time()
    knn = KNeighborsClassifier(n_neighbors=6)
    knn.fit(train_inputs[
                  ['A','B','C','D','E','F','G','H','I','J','K','L','M']], train_targets)
    pre_knn = knn.predict(test_inputs[
                                    ['A','B','C','D','E','F','G','H','I','J','K','L','M']])
    score_knn = accuracy_score(test_targets, pre_knn)
    end = time.time()
    score_knn = score_knn * 100
    return round(score_knn, 5), round((end - start), 3)

def sensitivity_analysis(csv_path, epoch=50): #灵敏度分析函数
    epoch_flag = 0  # 周期计数器
    Ka_sum = 0  # Ka的真实总数
    Ka_Tsum = 0  # Ka的预测总数
    PbBa_sum = 0  # Ka的真实总数
    PbBa_Tsum = 0  # Ka的预测总数
    for j in range(epoch):
        test_inputs, test_targets, train_inputs, train_targets = data_reader(csv_path)

        knn = KNeighborsClassifier(n_neighbors=6)
        knn.fit(train_inputs[
                    ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M']], train_targets)
        preds_knn = knn.predict(test_inputs[
                                    ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M']])

        # 分别对真实和预测label进转换为ist
        true_label = test_targets[:].tolist()
        pre_label = preds_knn[:].tolist()
        print("epoch:", epoch_flag)
        epoch_flag += 1

        test_size = 20  # 测试集样本数
        i = 0
        Ka_count = 0
        PbBa_count = 0

        while i < test_size:
            if true_label[i] == 0:
                Ka_count += 1
            elif true_label[i] == 1:
                PbBa_count += 1
            else:  # 得到真实label里正数（Ka）的数量
                pass
            i += 1
        Ka_sum += Ka_count
        PbBa_sum += PbBa_count

        i = 0
        Ka_Tcount = 0
        PbBa_Tcount = 0
        while i < test_size:
            if true_label[i] == pre_label[i]:
                if pre_label[i] == 0:
                    Ka_Tcount += 1
                elif pre_label[i] == 1:
                    PbBa_Tcount += 1
                else:  # 得到预测label里正数（Ka）的数量
                    pass
            else:
                pass
            i += 1
        Ka_Tsum += Ka_Tcount
        PbBa_Tsum += PbBa_Tcount

        #进程显示窗口
        if Ka_count != 0:
            print("epoch:", epoch_flag, " Ka's sensitivity:", Ka_Tcount / Ka_count)
        else:
            pass

        if PbBa_count != 0:
            print("epoch:", epoch_flag, " PbBa's sensitivity:", PbBa_Tcount / PbBa_count)
        else:
            pass

    print("Ka's average sensitivity:", Ka_Tsum / Ka_sum)
    print("PbBa's average sensitivity:",PbBa_Tsum / PbBa_sum)

if __name__ == '__main__':
    csv_path = 'Q3-1.csv'#CSV的文件路径
    epoch = 1000  # 设置sensitivity的分析周期
sensitivity_analysis(csv_path, epoch)
