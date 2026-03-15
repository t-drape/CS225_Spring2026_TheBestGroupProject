class Node {
    public:
        int me;
        Node* next;
    Node() : next(NULL) {};
};

class LinkedList {
    public:
        Node* head;
        bool inList(int hue) {
            Node* testHead = head;
            while(testHead != NULL) {
                if (testHead->me == hue) {
                    return true;
                }
                testHead = testHead->next;
            }
            return false;
        }
        void addUnique(int hue) {
            if (inList(hue)) {
                return;
            }
            Node* np = new Node;
            np->me = hue;
            if (head == NULL) {
                head = np;
            } else {
                Node* testHead;
                testHead = head;
                while(testHead->next != NULL) {
                    testHead = testHead->next;
                }
                testHead->next = np;
            }
        }

        friend ostream& operator<<(ostream& os, LinkedList& ll) {
            Node* testHead = ll.head;
            while (testHead->next != NULL) {
                os << "Value: " << testHead->me << endl;
                testHead = testHead->next;
            }
            os << "Value: " << testHead->me << endl;
            return os;
        }
};

Node* matchingClothes(HSLColor* closet, int* hues) {
    int loops = 0;
    bool match = false;
    LinkedList head;
    head.head = NULL;
    /*
    Loop until match found,
    Each iteration, increase range by 10%, = add/subtract 36 degrees from each value
    */
    do {
        /*
        For clothes in partitioned closet,
        If hue is within range,
        Add to matchingColor Linked list of Clothes objects
        */
        for(int i = 0; i < 10; i++) {
            for (int j = 0; j < 4; j++) {
                /*
                Originally, I expanded both sides. This led to too many colors included.
                So, the lower bound equals the original value, the upper bound equals the computed value.
                */
                int upperBound = hues[j] + (36 * loops);
                if (upperBound > 359) {
                    upperBound -= 360;
                }
                if (inRange(closet[i].getHue(), hues[j], upperBound)) {
                    // Change to a Clothes Object once we have full project developed
                    head.addUnique(closet[i].getHue());
                    match = true;
                }
            }
        }
        loops++;
    } while (match == false);
    return head.head;

}