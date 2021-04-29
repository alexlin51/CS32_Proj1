#include <iostream>
#include <string>

using namespace std;

bool somePredicate(string s) {
	return s.empty();
}
// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
	if (n <= 0) {
		return true;
	}
	bool curr = somePredicate(*a);
	if (!curr) {
		return false;
	}
	else {
		return allTrue(a + 1, n - 1);
	}
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n <= 0) {
		return 0;
	}

	bool curr = somePredicate(*a);
	int num = 0;
	if (!curr) {
		num += 1;
	}
	
	return countFalse(a + 1, n - 1) + num;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	if (n <= 0) {
		return -1;
	}
	
	int spot = firstFalse(a + 1, n - 1);

	bool isTrue = somePredicate(*a);
	if (spot == -1) {
		if (!isTrue) {
			return 0;
		}
		else {
			return -1;
		}
	}

	if (!isTrue) {
		return 0;
	}
	else {
		return spot + 1;
	}
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
	if (n <= 0) {
		return -1;
	}

	if (n == 1) {
		return 0;
	}

	int mid = n / 2;
	int min1 = indexOfLeast(a, mid);
	int min2 = indexOfLeast(a + mid, n - mid) + mid;

	return (a[min1] < a[min2]) ? min1 : min2;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 <= 0) {
		return true;
	}
	if (n1 < n2) {
		return false;
	}

	if (a1[0] == a2[0]) {
		return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	}
	else {
		return includes(a1 + 1, n1 - 1, a2, n2);
	}
}

int main() {
	string test[5] = { "", "a", "", "", "a" };
	cout << firstFalse(test, 5) << endl;
	cout << allTrue(test, 5) << endl;
	cout << countFalse(test, 5) << endl;

	string test2[5] = { "b", "z", "c", "d", "a" };
	cout << indexOfLeast(test2, 5) << endl;

	string main[7] = { "stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters" };
	string mtest1[3] = { "kyle", "kenny", "butters" };
	string mtest2[3] = { "kyle", "cartman", "cartman" };
	string mtest3[3] = { "kyle", "butters", "kenny" };
	string mtest4[3] = { "stan", "kenny", "kenny" };
	cout << includes(main, 7, mtest1, 3) << endl;
	cout << includes(main, 7, mtest2, 3) << endl;
	cout << includes(main, 7, mtest3, 3) << endl;
	cout << includes(main, 7, mtest4, 3) << endl;
}