#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>

using namespace std;

// Constants for the number of points, values per point, clusters, and maximum iterations
const int POINTS = 150;
const int VALUES = 4;
const int CLUSTER_NUM = 3;
const int MAX_ITERATIONS = 100;

// Structure representing a point in the dataset
struct Point {
    int id_point, id_cluster; // Point ID and assigned cluster ID
    double values[VALUES]; // Feature values
    char name[50]; // Name of the point

    // Default constructor for initializing the point without values
    Point() {}

    // Parameterized constructor for initializing the point with values
    Point(int id, double vals[], const char* nm) {
        id_point = id;
        id_cluster = -1; // Initially, the -1 is for the point assigned to any cluster
        for (int i = 0; i < VALUES; i++) {
            values[i] = vals[i];
        }
        strncpy(name, nm, 49);
        name[49] = '\0'; // Ensures string termination
    }
};

// Structure of a cluster
struct Cluster {
    int id_cluster; // Cluster ID
    double central_values[VALUES]; // Centroid values of the cluster
    int total_points; // Total points assigned to this cluster

    // Default constructor
    Cluster() {}

    // Parameterized constructor initializing the cluster with the first assigned point
    Cluster(int id, Point point) {
        id_cluster = id;
        total_points = 0;
        for (int i = 0; i < VALUES; i++) {
            central_values[i] = point.values[i]; // Initial centroid is set to the first point's values
        }
    }
};

// K-Means clustering algorithm
struct KMeans {
    Cluster clusters[CLUSTER_NUM]; // Vector of clusters
    Point points[POINTS]; // Vector of points

    // Constructor initializing KMeans with dataset points
    KMeans(Point pts[]) {
        for (int i = 0; i < POINTS; i++) {
            points[i] = pts[i]; // Copy the points into the KMeans instance
        }
    }

    // Function to calculate the Euclidean distance between a point and the cluster centroids
    int EucliDistance(Point point) {
        double min_dist = 100.0; // Start with a large distance
        int id_cluster_center = 0;

        for (int i = 0; i < CLUSTER_NUM; i++) {
            double sum = 0.0;
            for (int j = 0; j < VALUES; j++) {
                sum += pow(clusters[i].central_values[j] - point.values[j], 2.0);
            }
            double dist = sqrt(sum);
            if (dist < min_dist) {
                min_dist = dist;
                id_cluster_center = i; // Assign point to the closest cluster
            }
        }
        return id_cluster_center;
    }

    // Runs the K-Means clustering algorithm
    void run() {
        int iter = 0;
    
        // Initialize clusters with the first few points
        for (int i = 0; i < CLUSTER_NUM; i++) {
            clusters[i] = Cluster(i, points[i]);
        }
        
        bool done = false; // Iniciating the done variable to false to start the loop
        while (iter < MAX_ITERATIONS && !done) {
            done = true;
            int cluster_counts[CLUSTER_NUM] = {0}; // Count of points in each cluster
            double new_centers[CLUSTER_NUM][VALUES] = {0}; // Temporary storage for new centroids
    
            // Assign each point to the nearest cluster
            for (int i = 0; i < POINTS; i++) {
                int id_nearest_center = EucliDistance(points[i]);
                if (points[i].id_cluster != id_nearest_center) {
                    points[i].id_cluster = id_nearest_center;
                    done = false; // Clusters changed, so we continue iterating
                }
    
                cluster_counts[id_nearest_center]++;
                for (int j = 0; j < VALUES; j++) {
                    new_centers[id_nearest_center][j] += points[i].values[j];
                }
            }
    
            // Compute new centroids
            for (int i = 0; i < CLUSTER_NUM; i++) {
                if (cluster_counts[i] > 0) {
                    for (int j = 0; j < VALUES; j++) {
                        clusters[i].central_values[j] = new_centers[i][j] / cluster_counts[i];
                    }
                }
            }
    
            iter++;
        }
    }

    // Function to print the final clusters and their assigned points
    void printClusters() {
        cout << "Final clusters after " << MAX_ITERATIONS << " iterations:\n";
        for (int i = 0; i < CLUSTER_NUM; i++) {
            cout << "Cluster " << i + 1 << ":\n";
            for (int j = 0; j < POINTS; j++) {
                if (points[j].id_cluster == i) {
                    cout << "Point " << points[j].id_point + 1 << " (" << points[j].name << "): ";
                    for (int k = 0; k < VALUES; k++) {
                        cout << points[j].values[k] << " ";
                    }
                    cout << endl;
                }
            }
            cout << endl;
        }
    }
};

int main() {
    Point points[POINTS]; // Character vector to store dataset points

    string file_path;
    cout << "Enter the file path: ";
    cin >> file_path;

    // Open the dataset file
    ifstream file(file_path);
    if (!file) {
        cerr << "Error: Unable to open file " << file_path << endl;
        return 1;
    }

    // Read dataset points from the file
    for (int i = 0; i < POINTS; i++) {
        double values[VALUES];
        char point_name[50];

        // Read the feature values of the point
        for (int j = 0; j < VALUES; j++) {
            if (!(file >> values[j])) {
                cerr << "Error reading values for point " << i + 1 << endl;
                return 1;
            }
        }

        // Skip the line break after the numbers before reading the name
        file.ignore();

        // Read the name of the point
        file.getline(point_name, 50);

        // Store the point in the array
        points[i] = Point(i, values, point_name);
    }

    file.close(); // Close the dataset file

    // Run K-Means algorithm
    KMeans kmeans(points);
    kmeans.run();
    kmeans.printClusters();

    return 0;
}