#include "../Searcher.h"
int main() {
    ns_searcher::Searcher s;
    s.InitSearch("./data/raw_html/raw.txt");
    while (1) {
        string key;
        cout << "Please Input#";
        cin >> key;
        cout << s.Search(key);
    }
    return 0;
}