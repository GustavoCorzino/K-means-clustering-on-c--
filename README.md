# **K-Means Clustering in C++**

## *Overview*

This project was created as part of a course in the discipline of Algorithms. It implements the K-Means clustering algorithm in C++ to classify a set of points into clusters based on their feature values. The program reads data from a file, assigns each point to the nearest cluster, updates the cluster centroids iteratively, and outputs the final cluster assignments.

#### Features:

. Reads data from a file containing 150 points with 4 feature values each.

. Uses the Euclidean distance to assign points to clusters.

. Supports a configurable number of clusters (default: 3).

. Iterates up to 100 times or until convergence.

. Outputs the final cluster assignments.

### How It Works

. The program reads the dataset from a specified file.

. It initializes cluster centroids with the first three points.

. In each iteration:

. Assigns each point to the nearest cluster using the Euclidean distance.

. Updates cluster centroids based on the mean of assigned points.

. Stops if cluster assignments remain unchanged for 10 iterations or after 100 iterations.

. Outputs the final clusters.

### File Format

- The input file must contain 150 lines, each with four numerical values followed by a string (point name). Example:

5.1 3.5 1.4 0.2 Iris-setosa
4.9 3.0 1.4 0.2 Iris-setosa
...

### Notes

The constants for the number of clusters (CLUSTER_NUM), features per point (VALUES), and maximum iterations (MAX_ITERATIONS) are defined at the beginning of the code.

. The Point structure stores data points with their feature values and names.

. The Cluster structure holds the cluster centroids and assigned points.

. The KMeans structure implements the clustering algorithm.
