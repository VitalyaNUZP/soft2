#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
//функція виводу рядка 
void showLine(vector<int> line) {

	static int step = 1;
	cout << endl;
	for (auto i = line.begin(); i != line.end(); ++i) {
		cout << (*i) + 1;
		if (*i != line.back()) {
			cout << "->";
		}
	}
	step++;
}

//функція пошуку потоку за алгоритмом Форда-Фалкерсона
int flow(vector<vector<int>> matrix, int start = 0, int to = 5) {
	vector<vector<int>> temp;//матриця потоків
	vector<int> min_cut_has;//масив для зберігання мінімального різниці потоків
	vector<string> min_cut;//масив для зберігання мінімального різниці потоків
	temp.assign(matrix.begin(), matrix.end());
	int max_flow = 0;

	while (true) {
		bool isExit = false;

		int count = matrix.size();

		vector<bool> visited(count, false);
		queue<int> arr;
		vector<int> list, capacity, from, line;

		list.clear();
		min_cut.clear();
		min_cut_has.clear();

		arr.push(start);
		visited[start] = true;

		while (!arr.empty()) {
			if (isExit) break;

			int first = arr.front();

			arr.pop();

			for (int i = 0; i < count; i++) {
				if (first == i) continue;


				if ((matrix[first][i]) && (!visited[i]) && matrix[first][i] > 0) {
					visited[i] = true;
					arr.push(i);
					from.push_back(first);
					list.push_back(i);

					if (to == i) {
						isExit = true;
						break;
					}
				}
				else if (((matrix[i][first]) && (!visited[i]) && matrix[i][first] > 0)) {
					visited[i] = true;
					arr.push(i);
					list.push_back(i);
					from.push_back(first);
					if (to == first) {
						isExit = true;
						break;
					}
				}
				else if (((!matrix[i][first]) && (!visited[i]) && temp[i][first])) {
					visited[i] = true;
					arr.push(i);
					list.push_back(i);
					from.push_back(first);
					if (to == first) {
						isExit = true;
						break;
					}
				}


			}
		}

		if (list.empty() || list[list.size() - 1] != to) break;

		line.push_back(list[list.size() - 1]);
		int  index = list.size() - 1;

		while (1) {
			line.push_back(from[index]);
			if (start == from[index]) break;
			for (int i = 0; i < list.size(); i++) {
				if (list[i] == from[index]) {
					index = i;
					break;
				}
			}
		}

		reverse(line.begin(), line.end());

		showLine(line);

		for (int i = 0; i < line.size() - 1; i++) {
			if (!matrix[line[i]][line[i + 1]]) {
				if (!matrix[line[i + 1]][line[i]]) {
					capacity.push_back(1000000);
					continue;
				}
				capacity.push_back(1000000);
				continue;
			}
			capacity.push_back(matrix[line[i]][line[i + 1]]);
		}

		int minimal = *min_element(capacity.begin(), capacity.end());

		max_flow += minimal;

		for (int i = 0; i < line.size() - 1; i++) {
			if (capacity[i] == matrix[line[i]][line[i + 1]]) {
				matrix[line[i]][line[i + 1]] -= minimal;
			}
			else {
				matrix[line[i + 1]][line[i]] += minimal;
			}
		}
		cout << " (" << minimal << ')' << endl;
	}
	return max_flow;
}

int main() {
	setlocale(LC_ALL, "");
	int count = 0;
	cout << "Введiть розмiрнiсть матрицi: ";
	cin >> count;

	vector<vector<int>> matrix(count);
	cout << "\n	";
	for (int i = 0; i < count; i++)
		cout << ' ' << i + 1;
	cout << "\n\n";
	for (int i = 0; i < count; i++) {
		matrix[i].resize(count);
		cout << i + 1 << "	 ";
		for (int j = 0; j < count; j++) {
			cin >> matrix[i][j];

		}
	}
	cout << endl << "Максимальний потiк = " << flow(matrix, 0, matrix.size() - 1) << endl;

	system("pause");
	return 0;
}
