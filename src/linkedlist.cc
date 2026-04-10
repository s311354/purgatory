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

    while (fast) {
	// branch prediction
	ListNode *next = fast->next;
	if (!next) break;

	// cpu pipeline
        slow = slow->next;
	fast = next->next;

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

	// compiler optimization
        if (sum >= 10) {
	    carry = 1;
	    sum -= 10;
	} else {
	    carry = 0;
	}

        tail->next = new ListNode(sum);
	tail = tail->next;
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

    for (int i = 0; i <= n; ++i) {
        fast = fast->next;
    }

    // cpu pipeline
    while(fast) {
        fast = fast->next;
	slow = slow->next;
    }

    if (slow->next) {
	// cpu pipeline
        ListNode* toDelete = slow->next;
        slow->next = toDelete->next;
        delete toDelete;
    }

    return dummy.next;
}

/*
 *  using dummy node and iterative reversal here because we can break the list into chunks of k nodes and reverse pointers in-place
 *  T: O(n), S: O(1)
 */
ListNode* Purgatory::reverseKGroup(ListNode* head, int k) {
    if (!head || k <= 1) return head;

    // cpu pipeline
    int len = 0;
    for (ListNode *p = head; p; p = p->next) len++;

    ListNode dummy(0);
    dummy.next = head;

    ListNode* prevGroupEnd = &dummy;

    // branch prediction
    for (int g = 0; g < len / k; ++g) {
	// register vs memory
        ListNode *curr = prevGroupEnd->next;
	ListNode *prev = nullptr;

	for (int i = 0; i < k; ++i) {
            ListNode *next = curr->next;
	    curr->next = prev;
	    prev = curr;
	    curr = next;
	}

        // cpu pipeline
        ListNode *tail = prevGroupEnd->next;
	prevGroupEnd->next = prev;
	tail->next = curr;
	prevGroupEnd = tail;
    }

    return dummy.next;
}





}
