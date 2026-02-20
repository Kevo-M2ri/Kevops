#include <iostream>
#include "clist.h"

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-variable"

int main()
{
    node* head{nullptr};

    /* Builds a circular linked list with a random number of nodes
    *containing randomly-chosen numbers.
    */
    build(head);
	
    display(head);
    
    cout << "iterative number of nodes count: " << count(head) << endl;
    cout << "recursive number of nodes count: " << countR(head) << endl;
    cout << "iterative sum: " << sum(head) << endl;
    cout << "recursive sum: " << sumR(head) << endl;
	

    // When called the 2nd time, this also prints the total
	// of the numbers in the nodes.
    display(head);

	
	int		nNodesFreed{0};
	node*	n{head};
	node* 	temp;

	while( n != head || ! nNodesFreed) {
		temp = n->next;
		delete n;
		n = temp;
		nNodesFreed++;

		}
	cout << "# nodes freed: " << nNodesFreed << endl;
	

	//destroy(head);

    return 0;
}
