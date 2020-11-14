# -*- coding: utf-8 -*-
"""
Created on Fri Nov 13 15:19:48 2020

@author: Jerry
"""

from sklearn import datasets
iris=datasets.load_iris()
iris_X=iris.data
iris_Y=iris.target

#切分
from sklearn.model_selection import train_test_split
X_train,X_test,Y_train,Y_test = train_test_split(iris_X, iris_Y, test_size=0.2)

#训练
from sklearn.neighbors import KNeighborsClassifier
knn=KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train,Y_train)

#test
print(knn.predict_proba(X_test))
print(Y_test)
print(knn.score(X_test, Y_test))