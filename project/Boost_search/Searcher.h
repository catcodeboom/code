#pragma once
#include "/home/slowstep/LinuxLearning/project/Boost_search/index.h"
#include <jsoncpp/json/json.h>
namespace ns_searcher {
    class Searcher {
    public:
        static void InitSearch(const string &file_path) { // 进行初始化,构建索引
            ns_index::Index::GetInst()->BulidIndex(file_path);
        }
        static string Search(const string &query) { // 根据用户请求,返回结果
            // 1.分词
            vector<string> words;
            JiebaUtil::CutString(query, words);
            // 将words中的所有空串去掉,例如"   "、"          "
            for (auto it = begin(words); it != end(words);) {
                bool flag = false;
                for (char c : *it) {
                    if (c != ' ') {
                        flag = true;
                        break;
                    }
                }
                if (flag) {
                    it++;
                } else {
                    it = words.erase(it);
                }
            }
            // 2.触发
            using namespace ns_index;
            unordered_map<int, InvertedElmePrint> hash; // doc_id ---> doc_id + vector<string> words + weight
            for (string &word : words) {
                boost::to_lower(word);
                // 根据词进行查找
                auto Invertedlist = ns_index::Index::GetInst()->GetInvertedList(word); // 获取倒排拉链
                if (Invertedlist == nullptr) {
                    continue; // 表示这个关键字不存在
                }
                // cout << "关键字" << word << "对应的文档有" << Invertedlist->size() << "篇" << endl;
                for (auto &epair : *Invertedlist) { // 遍历文档
                    hash[epair.doc_id].doc_id = epair.doc_id;
                    hash[epair.doc_id].weight += epair.weight; // 权值进行累加
                    hash[epair.doc_id].words.push_back(word);
                }
                // cout << "存储key-val哈希表的表大小为: " << hash.size() << endl;
            }
            vector<InvertedElmePrint> allElme;
            for (auto &epair : hash) {
                allElme.push_back(move(epair.second));
            }
            // 对allElem中的结果按照权值进行排序(降序)
            std::sort(begin(allElme), end(allElme), [](const InvertedElmePrint &l, const InvertedElmePrint &r) { return l.weight > r.weight; });
            Json::Value root;
            for (auto &item : allElme) {
                // item中保存了id,word和权值
                auto doc = Index::GetInst()->GetForwardIndex(item.doc_id);
                assert(doc != nullptr); // 理论上doc不可能为nullptr,因为item是根据倒排索引得到的,倒排索引又依赖于正排索引构建
                Json::Value temp;
                temp["title"] = doc->title;
                temp["content"] = GetDesc(doc->content, item.words[0]); // 获取摘要
                temp["url"] = doc->url;
                temp["weight"] = item.weight;
                // temp["weight"] = item.weight;
                // temp["doc_id"] = item.doc_id;
                root.append(temp);
            }
            return Json::FastWriter().write(root); // 返回序列化后的结果
        }

        // static string Search(const string &query) { // 根据用户请求,返回序列化后的字符串
        //     // 1.分词
        //     vector<string> words;
        //     JiebaUtil::CutString(query, words);
        //     for (auto it = begin(words); it != end(words);) {
        //         bool flag = false;
        //         for (char c : *it) {
        //             if (c != ' ') {
        //                 flag = true;
        //                 break;
        //             }
        //         }
        //         if (flag) {
        //             it++;
        //         } else {
        //             it = words.erase(it);
        //         }
        //     }
        //     // 2.触发
        //     using namespace ns_index;
        //     vector<InvertedElme> allElme; // 保存所有根据关键词拿到的结果
        //     for (string &word : words) {
        //         boost::to_lower(word);
        //         // 根据词进行查找
        //         auto Invertedlist = ns_index::Index::GetInst()->GetInvertedList(word); // 获取倒排拉链
        //         if (Invertedlist == nullptr) {
        //             continue; // 表示这个关键字不存在
        //         }
        //         allElme.insert(std::end(allElme), Invertedlist->begin(), Invertedlist->end());
        //     }
        //     // 对allElem中的结果按照权值进行排序(降序)
        //     std::sort(begin(allElme), end(allElme), [](const InvertedElme &l, const InvertedElme &r) { return l.weight > r.weight; });
        //     // 3.根据结果构建序列化后的字符串并进行返回
        //     Json::Value root;
        //     for (auto &item : allElme) {
        //         // item中保存了id,word和权值
        //         auto doc = Index::GetInst()->GetForwardIndex(item.doc_id);
        //         assert(doc != nullptr); // 理论上doc不可能为nullptr,因为item是根据倒排索引得到的,倒排索引又依赖于正排索引构建
        //         Json::Value temp;
        //         temp["title"] = doc->title;
        //         temp["content"] = GetDesc(doc->content, item.word); // 获取摘要
        //         temp["url"] = doc->url;
        //         root.append(temp);
        //     }
        //     return Json::StyledWriter().write(root); // 返回序列化后的结果
        // }
        static string GetDesc(const string &content, const string &word) {
            // boost::to_lower(content); // 将content转换为小写,进行忽略大小写的查找
            auto it = std::search(begin(content), end(content), begin(word), end(word), [](char x, char y) -> bool { return std::tolower(x) == std::tolower(y); });
            assert(it != end(content));
            size_t firstpos = std::distance(begin(content), it);
#define PREV_SIZE 50
#define NEXT_SIZE 100
            size_t start = 0;
            size_t end = size(content) - 1;
            if (start + PREV_SIZE < firstpos) {
                start = firstpos - PREV_SIZE;
            }
            if (firstpos + NEXT_SIZE <= end) {
                end = firstpos + NEXT_SIZE;
            }
            return content.substr(start, end - start + 1) + "......";
        }
    };
} // namespace ns_searcher