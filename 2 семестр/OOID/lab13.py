from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler
from sklearn.datasets import make_blobs
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.datasets import load_breast_cancer
import mglearn
import sklearn
import matplotlib.pyplot as plt

"In[2]:"
mglearn.plots.plot_scaling()
plt.show()

"In[3]:"
cancer = load_breast_cancer()
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, random_state=1)
print(X_train.shape)
print(X_test.shape)

"In[4]:"
scaler = MinMaxScaler()

"In[5]:"
scaler.fit(X_train)

"In[6]:"
min_on_training = X_train.min(axis=0)
range_on_training = (X_train-min_on_training).max(axis=0)

X_train_scaled = (X_train-min_on_training)/range_on_training
print("формапреобразованногомассива:{}".format(X_train_scaled.shape))
print("minзначениепризнакадомасштабирования:\n{}".format(X_train.min(axis=0)))
print("maxзначениепризнакадомасштабирования:\n{}".format(X_train.max(axis=0)))
print("minзначениепризнакапослемасштабирования:\n{}".format(
    X_train_scaled.min(axis=0)))
print("maxзначениепризнакапослемасштабирования:\n{}".format(
    X_train_scaled.max(axis=0)))

"In[7]:"
X_test_scaled = (X_test-min_on_training)/range_on_training
print("minзначениепризнакапослемасштабирования:\n{}".format(
    X_test_scaled.min(axis=0)))
print("maxзначениепризнакапослемасштабирования:\n{}".format(
    X_test_scaled.max(axis=0)))

"In[8]:"
X, _ = make_blobs(n_samples=50, centers=5, random_state=4, cluster_std=2)
X_train, X_test = train_test_split(X, random_state=5, test_size=.1)
fig, axes = plt.subplots(1, 3, figsize=(13, 4))
axes[0].scatter(X_train[:, 0], X_train[:, 1],
                c=mglearn.cm2(0), label="Обучающийнабор", s=60)
axes[0].scatter(X_test[:, 0], X_test[:, 1], marker='^',
                c=mglearn.cm2(1), label="Тестовыйнабор", s=60)
axes[0].legend(loc='upper left')
axes[0].set_title("Исходныеданные")
scaler = MinMaxScaler()
scaler.fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)

axes[1].scatter(X_train_scaled[:, 0], X_train_scaled[:, 1],
                c=mglearn.cm2(0), label="Обучающийнабор", s=60)
axes[1].scatter(X_test_scaled[:, 0], X_test_scaled[:, 1],
                marker='^', c=mglearn.cm2(1), label="Тестовыйнабор", s=60)
axes[1].set_title("Масштабированныеданные")
test_scaler = MinMaxScaler()
test_scaler.fit(X_test)
X_test_scaled_badly = test_scaler.transform(X_test)
axes[2].scatter(X_train_scaled[:, 0], X_train_scaled[:, 1],
                c=mglearn.cm2(0), label="Обучающийнабор", s=60)
axes[2].scatter(X_test_scaled_badly[:, 0], X_test_scaled_badly[:, 1],
                marker='^', c=mglearn.cm2(1), label="Тестовыйнабор", s=60)
axes[2].set_title("Неправильномасштабированныеданные")

for ax in axes:
    ax.set_xlabel("Признак0")
    ax.set_ylabel("Признак1")

plt.show()

"In[9]:"
scaler = StandardScaler()
X_scaled = scaler.fit(X).transform(X)
X_scaled_d = scaler.fit_transform(X)

"In[10]:"
X_train, X_test, y_train, y_test = train_test_split(
    cancer.data, cancer.target, random_state=0)
svm = SVC(C=100)
svm.fit(X_train, y_train)
print("Правильностьнатестовомнаборе:{:.2f}".format(svm.score(X_test, y_test)))

"In[11]:"
scaler = MinMaxScaler()
scaler.fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)
svm.fit(X_train_scaled, y_train)
print("Правильностьнамасштабированномтестовомнаборе:{:.2f}".format(
    svm.score(X_test_scaled, y_test)))

"In[12]:"
scaler = StandardScaler()
scaler.fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)
svm.fit(X_train_scaled, y_train)
print("ПравильностьSVMнатестовомнаборе:{:.2f}".format(
    svm.score(X_test_scaled, y_test)))
