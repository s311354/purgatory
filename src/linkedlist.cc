#include "purgatory.h"

namespace purgatory {

/*
 *  using two pointers algorithm here because we can break the problem into simulates two runners on a track, if the track loops, they'll meet eventually
 *  T: O(n), S: O(1)
 */
bool Purgatory::hasCycle(ListNode* head) {
    if (!head || !head->next) 
        return false;

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
	fast = fast->next->next;

	if (slow == fast)
	    return true;
    }

    return false;
}

/*
 *  using two pointer traversal + carry propagation approach here because we can break the problem into repeated single-digit additions, each iteration depends only on the previous carry.
 *  T: O(max(m, n)), S: O(max(m, n))
 */
ListNode* Purgatory::addTwoNumber(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);

    ListNode* tail = &dummy;

    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;

	if (l1) {
	    sum += l1->val;
	    l1 = l1->next;
	}

	if (l2) {
	    sum += l2->val;
	    l2 = l2->next;
	}


        tail->next = new ListNode(sum%10);
	tail = tail->next;
	carry = sum/10;
    }

    return dummy.next;
}

/*
 *  using the dummy-node + two-pointer pattern here because we can break the problem into ... two parts
 *  - maintain a fixed gap of n between two pointers
 *  - use that gap to locate the node before the target in one pass.
 *  T: O(n), S: O(1)
 */
ListNode* Purgatory::removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;

    ListNode *fast = &dummy;
    ListNode *slow = &dummy;

    for (int i = 0; i < n; ++i) {
        fast = fast->next;
    }

    while(fast->next) {
        fast = fast->next;
	slow = slow->next;
    }

    ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;

    return dummy.next;
}

/*
 *  using dummy node and iterative reversal here because we can break the list into chunks of k nodes and reverse pointers in-place
 *  T: O(n), S: O(1)
 */
ListNode* Purgatory::reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0);
    dummy.next = head;

    ListNode* prevGroupEnd = &dummy;

    while(true) {
        ListNode* kth = prevGroupEnd;

	for (int i = 0; i < k && kth; ++i) {
	    kth = kth->next;
	}

	if (!kth)
	    break;

	ListNode* nextGroupStart = kth->next;

	// reverse the current group
	ListNode* curr = prevGroupEnd->next;
	ListNode* prev = nextGroupStart;
	while(curr != nextGroupStart) {
            ListNode* temp = curr->next;
	    curr->next = prev;
	    prev = curr;
	    curr = temp;
	}

        ListNode* temp = prevGroupEnd->next;
	prevGroupEnd->next = kth;
	prevGroupEnd = temp;
    }

    return dummy.next;
}





}
