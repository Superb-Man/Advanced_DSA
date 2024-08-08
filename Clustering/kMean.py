import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class KMeans:
    def __init__(self, k, max_iters=100, tol=1e-4):
        self.k = k
        self.max_iters = max_iters
        self.tol = tol

    def initialize_centroids(self, X):
        return X[np.random.choice(X.shape[0], self.k, replace=False)]

    def compute_distances(self, X, centroids):
        distances = np.zeros((X.shape[0], self.k))
        for i in range(self.k):
            distances[:, i] = np.linalg.norm(X - centroids[i], axis=1)
        return distances

    def compute_responsibilities(self, distances):
        return np.argmin(distances, axis=1)

    def update_centroids(self, X, labels):
        centroids = np.zeros((self.k, X.shape[1]))
        for i in range(self.k):
            centroids[i] = X[labels == i].mean(axis=0)
        return centroids

    def fit(self, X):
        self.X = X
        self.centroids = self.initialize_centroids(X)
        self.labels = np.zeros(X.shape[0])

        fig, ax = plt.subplots()
        
        def init():
            ax.clear()
            ax.scatter(X[:, 0], X[:, 1], c='gray')
            return ax,

        def update(frame):
            ax.clear()
            distances = self.compute_distances(self.X, self.centroids)
            self.labels = self.compute_responsibilities(distances)
            new_centroids = self.update_centroids(self.X, self.labels)

            if np.allclose(self.centroids, new_centroids, rtol=self.tol):
                self.ani.event_source.stop()
            self.centroids = new_centroids
            ax.scatter(self.X[:, 0], self.X[:, 1], c=self.labels, cmap='viridis', alpha=0.6)
            ax.scatter(self.centroids[:, 0], self.centroids[:, 1], marker='x', c='red')
            return ax,

        self.ani = animation.FuncAnimation(fig, update, frames=self.max_iters, init_func=init, blit=False, repeat=False)
        plt.title('K-Means Clustering with E-M Steps')
        plt.show()

        return self.centroids, self.labels

if __name__ == '__main__':
    np.random.seed(0)
    points_per_cluster = 100
    clusters = 5
    data = []

    for i in range(clusters):
        cluster_points = np.random.randn(points_per_cluster, 2) + np.array([i, i])
        data.append(cluster_points)

    X = np.vstack(data)

    kmeans = KMeans(k=5)
    centroids, labels = kmeans.fit(X)
