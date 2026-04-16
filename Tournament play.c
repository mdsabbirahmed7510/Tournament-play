#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char teamName[50];
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->teamName, "TBD");
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree(int n) {
    if (n <= 0) return NULL;
    if (n == 1) return createNode();

    Node* root = createNode();
    int leftCount = n / 2;
    int rightCount = n - leftCount;

    root->left = buildTree(leftCount);
    root->right = buildTree(rightCount);
    return root;
}

void assignTeams(Node* root, int* count) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        printf("Enter the team name of team %d: ", ++(*count));
        scanf("%s", root->teamName);
        return;
    }
    assignTeams(root->left, count);
    assignTeams(root->right, count);
}

void playMatches(Node* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return;

    playMatches(root->left);
    playMatches(root->right);

    printf("\nMatch: %s vs %s\n", root->left->teamName, root->right->teamName);
    printf("Enter Winner Name: ");
    scanf("%s", root->teamName);
}

void preOrder(Node* root) {
    if (root == NULL) return;
    printf("[%s] ", root->teamName);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("[%s] ", root->teamName);
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("[%s] ", root->teamName);
}

int main() {
    int numTeams;
    printf("Enter number of teams: ");
    scanf("%d", &numTeams);

    Node* tournamentRoot = buildTree(numTeams);

    int count = 0;
    assignTeams(tournamentRoot, &count);

    printf("\n--- Tree Traversals (Initial) ---\n");
    printf("Preorder: "); preOrder(tournamentRoot); printf("\n");
    printf("Inorder:  "); inOrder(tournamentRoot);  printf("\n");
    printf("Postorder: "); postOrder(tournamentRoot); printf("\n");

    printf("\n--- Starting Tournament Rounds ---\n");
    playMatches(tournamentRoot);

    printf("\n==============================\n");
    printf("Tournament Champion: %s\n", tournamentRoot->teamName);
    printf("==============================\n");

    return 0;
}
