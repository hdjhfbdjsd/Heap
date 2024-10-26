#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <utility> // For std::pair

//  ⁄—Ì› ›∆… «·ÂÌ»
class Heap {
private:
    std::vector<int> heap;

    int parent(int index) const {
        return (index - 1) / 2;  // Return the index of the parent element
    }

    int leftChild(int index) const {
        return 2 * index + 1;  // Return the index of the left child
    }

    int rightChild(int index) const {
        return 2 * index + 2;  // Return the index of the right child
    }

    void heapifyUp(int index) {
        while (index > 0 && heap[index] > heap[parent(index)]) {
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = leftChild(index);
            int right = rightChild(index);
            int largest = index;

            // Find the largest element
            if (left < size && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < size && heap[right] > heap[largest]) {
                largest = right;
            }

            // If the largest is different from the current index, swap them
            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    void insert(int element) {
        heap.push_back(element);  // Add the element to the heap
        heapifyUp(heap.size() - 1);  // Maintain the heap property
    }

    int extractMax() {
        if (heap.empty()) return -1;  // Heap is empty
        int maxElement = heap[0];  // The maximum element
        heap[0] = heap.back();  // Replace the maximum element with the last element
        heap.pop_back();  // Remove the last element
        heapifyDown(0);  // Maintain the heap property
        return maxElement;
    }

    int extractMin() {
        if (heap.empty()) return -1;  // Heap is empty
        return *std::min_element(heap.begin(), heap.end());  // Extract the minimum element
    }

    const std::vector<int>& getHeap() const {
        return heap;  // Return the heap
    }
};

//  ⁄—Ì› ›∆… ﬁ«∆„… «·√Ê·ÊÌ« 
class PriorityQueue {
private:
    std::vector<std::pair<int, int>> queue; // Pair of <priority, element>
    Heap heap; // Use heap for priority management

    // Maintain the heap property for the priority queue
    void maintainHeap() {
        heap = Heap(); // Clear the heap
        for (auto& p : queue) {
            heap.insert(p.first); // Insert only the priority
        }
    }

public:
    void insertWithPriority(int element, int priority) {
        queue.emplace_back(priority, element); // Store element with its priority
        maintainHeap(); // Maintain the heap property
    }

    int extractHighestPriority() {
        if (queue.empty()) return -1; // Queue is empty
        int maxPriority = heap.extractMax(); // Get the highest priority
        // Remove the element with the highest priority from queue
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            if (it->first == maxPriority) {
                int extractedElement = it->second;
                queue.erase(it); // Remove it from the queue
                return extractedElement; // Return the associated element
            }
        }
        return -1; // If not found
    }
};

//  ‰›Ì– ›—“ «·ÂÌ»
std::vector<int> heapSort(std::vector<int>& array) {
    Heap heap;
    for (int element : array) {
        heap.insert(element);  // Insert all elements into the heap
    }

    std::vector<int> sortedArray;
    while (!heap.getHeap().empty()) {
        sortedArray.insert(sortedArray.begin(), heap.extractMax());  // Extract max repeatedly
    }
    return sortedArray; // Return sorted array
}

// «·œ«·… «·—∆Ì”Ì…
int main() {
    int choice;
    do {
        std::cout << "Choose an option:\n";
        std::cout << "1. Use Heap\n";
        std::cout << "2. Use Priority Queue\n";
        std::cout << "3. Use Heap Sort\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // «Œ »«— «·ÂÌ»
                Heap heap;
                std::string input;
                std::cout << "Enter the elements for the heap separated by spaces (press Enter to finish): ";
                std::cin.ignore(); // Ignore the newline character
                std::getline(std::cin, input);
                std::istringstream iss(input);
                int element;

                // User input for inserting elements
                while (iss >> element) {
                    heap.insert(element);
                }

                std::cout << "Heap after insertions: ";
                for (int val : heap.getHeap()) std::cout << val << " ";
                std::cout << "\nMaximum element extracted: " << heap.extractMax() << "\n";

                std::cout << "Heap after extracting the maximum value: ";
                for (int val : heap.getHeap()) std::cout << val << " ";
                std::cout << "\nMinimum element in the heap: " << heap.extractMin() << "\n";
                break;
            }
            case 2: {
                // «Œ »«— ﬁ«∆„… «·√Ê·ÊÌ« 
                PriorityQueue pq;
                std::string input;
                std::cout << "\nEnter the elements and their priorities in the format 'element priority' (press Enter to finish):\n";
                std::cout << "Example: 10 1\n20 3\n5 2\n\n";
                std::cin.ignore(); // Ignore the newline character
                while (std::getline(std::cin, input) && !input.empty()) {
                    std::istringstream iss(input);
                    int element, priority;
                    if (iss >> element >> priority) {
                        pq.insertWithPriority(element, priority);
                    } else {
                        std::cout << "Invalid input. Please enter in the format 'element priority'.\n";
                    }
                }

                std::cout << "Extracting highest priority elements:\n";
                while (true) {
                    int element = pq.extractHighestPriority();
                    if (element == -1) break; // Stop if the queue is empty
                    std::cout << "Extracted element: " << element << "\n";
                }
                break;
            }
            case 3: {
                // «Œ »«— ›—“ «·ÂÌ»
                std::vector<int> arr;
                std::string input;
                std::cout << "\nEnter elements to sort using heap sort (press Enter to finish): ";
                std::cin.ignore(); // Ignore the newline character
                std::getline(std::cin, input);
                std::istringstream iss(input);
                int element;

                // User input for inserting elements for sorting
                while (iss >> element) {
                    arr.push_back(element);
                }

                std::vector<int> sortedArr = heapSort(arr);
                std::cout << "Sorted array using Heap Sort: ";
                for (int val : sortedArr) std::cout << val << " ";
                std::cout << "\n";
                break;
            }
            case 4:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
