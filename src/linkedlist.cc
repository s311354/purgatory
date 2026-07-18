#include "purgatory.h"

namespace purgatory {

/*
 *  using two pointers algorithm here because we can break the problem into
 * simulates two runners on a track, if the track loops, they'll meet eventually
 *  T: O(n), S: O(1)
 */
bool Purgatory::hasCycle(ListNode *head) {
  if (!head || !head->next)
    return false;

  ListNode *slow = head;
  ListNode *fast = head;

  while (fast) {
    // branch prediction
    ListNode *next = fast->next;
    if (!next)
      break;

    // cpu pipeline
    slow = slow->next;
    fast = next->next;

    if (slow == fast)
      return true;
  }

  return false;
}

/*
 *  using two pointer traversal + carry propagation approach here because we can
 * break the problem into repeated single-digit additions, each iteration
 * depends only on the previous carry. T: O(max(m, n)), S: O(max(m, n))
 */
ListNode *Purgatory::addTwoNumber(ListNode *l1, ListNode *l2) {
  ListNode dummy(0);

  ListNode *tail = &dummy;

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
 *  using the dummy-node + two-pointer pattern here because we can break the
 * problem into ... two parts
 *  - maintain a fixed gap of n between two pointers
 *  - use that gap to locate the node before the target in one pass.
 *  T: O(n), S: O(1)
 */
ListNode *Purgatory::removeNthFromEnd(ListNode *head, int n) {
  ListNode dummy(0);
  dummy.next = head;

  ListNode *fast = &dummy;
  ListNode *slow = &dummy;

  for (int i = 0; i <= n; ++i) {
    fast = fast->next;
  }

  // cpu pipeline
  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }

  if (slow->next) {
    // cpu pipeline
    ListNode *toDelete = slow->next;
    slow->next = toDelete->next;
    delete toDelete;
  }

  return dummy.next;
}

/*
 *  using dummy node and iterative reversal here because we can break the list
 * into chunks of k nodes and reverse pointers in-place T: O(n), S: O(1)
 */
ListNode *Purgatory::reverseKGroup(ListNode *head, int k) {
  if (!head || k <= 1)
    return head;

  // cpu pipeline
  int len = 0;
  for (ListNode *p = head; p; p = p->next)
    len++;

  ListNode dummy(0);
  dummy.next = head;

  ListNode *prevGroupEnd = &dummy;

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

bool Purgatory::isPalindromeLinkedList(ListNode *head) {
  if (!head || !head->next)
    return true;

  // register vs memory
  ListNode *slow = head, *fast = head;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *prev = nullptr;

  while (slow) {
    ListNode *next = slow->next;
    slow->next = prev;
    prev = slow;
    slow = next;
  }

  // register vs memory
  ListNode *p1 = head, *p2 = prev;

  while (p2) {
    if (p1->val != p2->val)
      return false;

    p1 = p1->next;
    p2 = p2->next;
  }

  return true;
}

ListNode *Purgatory::swapPairs(ListNode *head) {
  ListNode dummy(0);
  dummy.next = head;

  ListNode *prev = &dummy;

  while (true) {
    // branch prediction
    ListNode *first = prev->next;
    if (!first)
      break;

    // branch prediction
    ListNode *second = first->next;
    if (!second)
      break;

    ListNode *nextPair = second->next;

    prev->next = second;
    second->next = first;
    first->next = nextPair;

    prev = first;
  }

  return dummy.next;
}

ListNode *Purgatory::reorderList(ListNode *head) {
  if (!head)
    return nullptr;

  // register vs memory
  ListNode *slow = head, *fast = head;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *prev = nullptr, *curr = slow;
  while (curr) {
    ListNode *next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  // register vs memory
  ListNode *p1 = head, *p2 = prev;
  while (p2 && p2->next) {
    ListNode *n1 = p1->next;
    ListNode *n2 = p2->next;

    p1->next = p2;
    p2->next = n1;

    p1 = n1;
    p2 = n2;
  }

  return head;
}

int Purgatory::numComponents(ListNode *head, vector<int> &nums) {
  unordered_set<int> nodeSet(nums.begin(), nums.end());

  int componentCount = 0;

  for (ListNode *current = head; current; current = current->next) {

    // branch prediction
    if (!nodeSet.count(current->val))
      continue;

    // register vs memory
    ListNode *nextNode = current->next;

    if (!nextNode || !nodeSet.count(nextNode->val)) {
      ++componentCount;
    }
  }

  return componentCount;
}

vector<int> Purgatory::nodesBetweenCriticalPoints(ListNode *head) {
  if (!head || !head->next || !head->next->next)
    return {-1, -1};

  int currentIndex = 2;
  int firstCritical = -1;
  int previousCritical = -1;

  int minDistance = INT_MAX;

  ListNode *prev = head;
  ListNode *curr = head->next;

  while (curr->next) {
    // register vs memory
    int prevVal = prev->val;
    int currVal = curr->val;
    int nextVal = curr->next->val;

    // branch prediction
    bool isCritical = ((currVal > prevVal) && (currVal > nextVal)) ||
                      ((currVal < prevVal) & (currVal < nextVal));

    if (isCritical) {
      if (firstCritical == -1)
        firstCritical = currentIndex;

      if (previousCritical != -1)
        minDistance = min(minDistance, currentIndex - previousCritical);

      previousCritical = currentIndex;
    }

    prev = curr;
    curr = curr->next;
    ++currentIndex;
  }

  if (firstCritical == previousCritical)
    return {-1, -1};

  return {minDistance, previousCritical - firstCritical};
}

ListNode *reverseListRemoveNodes(ListNode *head) {
  ListNode *prev = nullptr;

  while (head) {
    ListNode *nextNode = head->next;
    head->next = prev;
    prev = head;
    head = nextNode;
  }

  return prev;
}

ListNode *Purgatory::removeNodes(ListNode *head) {
  if (!head || !head->next)
    return head;

  ListNode *reversedHead = reverseListRemoveNodes(head);

  int maxValue = reversedHead->val;

  ListNode *curr = reversedHead;

  while (curr && curr->next) {
    // register vs memory
    ListNode *nextNode = curr->next;

    // branch prediction
    const bool isDelete = nextNode->val < maxValue;

    if (isDelete) {
      curr->next = nextNode->next;
      delete nextNode;
    } else {
      curr = nextNode;
      maxValue = curr->val;
    }
  }

  return reverseListRemoveNodes(reversedHead);
}

ListNode *Purgatory::doubleIt(ListNode *head) {
  if (!head)
    return nullptr;

  ListNode *reversedHead = reverseListRemoveNodes(head);

  ListNode *currentNode = reversedHead;

  int carry = 0;

  ListNode *prevNode = nullptr;

  while (currentNode) {
    // register vs memory
    int doubledValue = (currentNode->val << 1) + carry;

    currentNode->val = doubledValue % 10;
    carry = doubledValue / 10;

    prevNode = currentNode;
    currentNode = currentNode->next;
  }

  if (carry)
    prevNode->next = new ListNode(carry);

  return reverseListRemoveNodes(reversedHead);
}

ListNode *Purgatory::middleNode(ListNode *head) {
  // register vs memory
  ListNode *first = head;
  ListNode *second = head;

  for (; second != nullptr && second->next != nullptr;
       second = second->next->next) {
    first = first->next;
  }

  return first;
}

ListNode *Purgatory::mergeNodes(ListNode *head) {
  // register vs memory
  ListNode *write = head;
  ListNode *curr = head->next;

  while (curr != nullptr) {
    // register vs memory
    int sum = 0;
    while (curr->val != 0) {
      sum += curr->val;
      curr = curr->next;
    }

    write->next->val = sum;
    write = write->next;

    curr = curr->next;
  }

  write->next = nullptr;
  return head->next;
}

ListNode *Purgatory::insertGreatestCommonDivisors(ListNode *head) {
  ListNode *curr = head;

  while (curr && curr->next) {
    ListNode *nextNode = curr->next;
    // register vs memory
    int a = curr->val, b = nextNode->val;

    while (b) {
      int t = a % b;
      a = b;
      b = t;
    }

    curr->next = new ListNode(a, nextNode);
    curr = nextNode;
  }

  return head;
}

ListNode *Purgatory::deleteDuplicates(ListNode *head) {
  ListNode *start = head;

  while (start && start->next) {
    // register vs memory
    int val = start->val;
    ListNode *nextNode = start->next;

    if (val == nextNode->val) {
      start->next = nextNode->next;
      delete nextNode;
    } else {
      start = start->next;
    }
  }

  return head;
}

ListNode *Purgatory::mergeInBetween(ListNode *list1, int a, int b,
                                    ListNode *list2) {
  ListNode *curr = list1;
  ListNode *first = nullptr, *second = nullptr;

  // branch prediction
  for (int i = 0; i < a - 1; ++i) {
    curr = curr->next;
  }
  first = curr;

  // branch prediction
  for (int i = 0; i < b - a + 2; ++i) {
    curr = curr->next;
  }
  second = curr;

  ListNode *merged = list2;
  while (merged->next)
    merged = merged->next;

  first->next = list2;
  merged->next = second;

  return list1;
}

ListNode *Purgatory::modifiedList(vector<int> &nums, ListNode *head) {

  // cache behavior
  vector<bool> buckets(100001, false);
  for (const int num : nums)
    buckets[num] = true;

  ListNode dummy(0);
  dummy.next = head;
  ListNode *tail = &dummy;

  ListNode *curr = head;

  while (curr) {
    // register vs memory
    int val = curr->val;
    if (buckets[val]) {
      tail->next = curr->next;
    } else {
      tail = curr;
    }

    curr = curr->next;
  }

  return dummy.next;
}

vector<int> Purgatory::nextLargerNodes(ListNode *head) {
  // cache behavior
  vector<int> nums;
  nums.reserve(100000);

  while (head) {
    nums.push_back(head->val);
    head = head->next;
  }

  // register vs memory
  int n = nums.size();
  vector<int> result(n, 0);
  stack<int> st;

  for (int i = 0; i < n; ++i) {
    // register vs memory
    int curr = nums[i];

    while (!st.empty()) {
      int topIdx = st.top();
      if (nums[topIdx] >= curr)
        break;

      result[topIdx] = curr;
      st.pop();
    }

    st.push(i);
  }

  return result;
}

ListNode *Purgatory::removeElements(ListNode *head, int val) {
  ListNode dummy(0);
  dummy.next = head;
  ListNode *tail = &dummy;

  while (tail->next) {
    // register vs memory
    ListNode *nextNode = tail->next;

    if (nextNode->val == val) {
      tail->next = nextNode->next;
      delete nextNode;
    } else {
      tail = nextNode;
    }
  }

  return dummy.next;
}

ListNode *Purgatory::reverseEvenLengthGroups(ListNode *head) {
  ListNode dummy(0);
  dummy.next = head;
  ListNode *tail = &dummy;

  ListNode *curr = head;

  // branch prediction
  for (int group = 1; curr; ++group) {
    ListNode *groupEnd = curr;
    int count = 0;

    while (count < group && groupEnd) {
      ++count;
      groupEnd = groupEnd->next;
    }

    // branch prediction
    if ((count & 1) == 0) {
      ListNode *prev = groupEnd;
      ListNode *node = curr;

      for (int i = 0; i < count; ++i) {
        ListNode *next = node->next;
        node->next = prev;
        prev = node;
        node = next;
      }

      tail->next = prev;
      tail = curr;
      curr = groupEnd;

    } else {
      for (int i = 0; i < count; ++i) {
        tail = curr;
        curr = curr->next;
      }
    }
  }
  return dummy.next;
}

int Purgatory::getDecimalValue(ListNode *head) {
  int result = 0;

  while (head) {
    result = (result << 1) | head->val;
    head = head->next;
  }

  return result;
}

ListNode *Purgatory::insertionSortList(ListNode *head) {
  ListNode dummy(0);
  ListNode *curr = head;
  ListNode *lastSorted = nullptr;

  while (curr) {
    ListNode *next = curr->next;

    // branch prediction
    ListNode *prev;
    if (!lastSorted || lastSorted->val > curr->val) {
      prev = &dummy;
    } else {
      prev = lastSorted;
    }

    while (prev->next && prev->next->val < curr->val)
      prev = prev->next;

    curr->next = prev->next;
    prev->next = curr;
    curr = next;

    lastSorted = prev;
  }

  return dummy.next;
}

} // namespace purgatory
