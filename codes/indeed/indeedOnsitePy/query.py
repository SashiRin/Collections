import sys
import time
import pprint
import operator

def start_function():
    user_map = dict()
    rank_table = {}
    line1 = "A Java PHP Python"
    line1 = input()
    update_user(line1, user_map)
    update_dict(line1, rank_table)

    line2 = "B C++ Python Java"
    line2 = input()
    update_user(line2, user_map)
    update_dict(line2, rank_table)

    line3 = "C Ruby C++ Scala Java"
    line3 = input()
    update_user(line3, user_map)
    update_dict(line3, rank_table)

    query1 = "C Python"
    query1 = input()
    query(query1, rank_table, user_map)


def update_user(line, user_map):
    split_string = line.split(' ', 1)
    user = split_string[0]
    words = split_string[1].split(' ')
    user_map[user] = words


def update_dict(line, relation_map):
    words = line.split(' ', 1)[1].split(' ')
    for word in words:
        if word not in relation_map.keys():
            relation_map[word] = dict()
        for w in words:
            if w != word:
                if w not in relation_map[word].keys():
                    relation_map[word][w] = 0
                    relation_map[word][w] += 1


def query(sntns, relation_map, user_map):
    split_string = sntns.split(' ')
    user = split_string[0]
    search_word = split_string[1]
    searched_list = user_map[user]
    for word in searched_list:
        if search_word not in relation_map[word].keys():
            relation_map[word][search_word] = 0
        relation_map[word][search_word] += 1
    if search_word not in relation_map.keys():
        relation_map[search_word] = dict()
    for word in searched_list:
        if word not in relation_map[search_word].keys():
            relation_map[search_word][word] = 0
        relation_map[search_word][word] += 1

    user_map[user].append(search_word)

    print(max(relation_map[search_word].items(), key=operator.itemgetter(1))[0])

    # pprint.pprint(user_map)
    # print()
    pprint.pprint(relation_map)





start_function()