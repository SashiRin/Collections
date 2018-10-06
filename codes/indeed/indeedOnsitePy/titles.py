# engineer "eng" -> ascii sum -> hash value > few hash colision

def start_from_here():
    words_list = ["software engineer", "data engineer", "machine learning engineer",
                  "senior infrastructure software engineer"]
    match_word = "senior software engineer"
    print(match_nearest_pos(words_list, match_word))


def match_nearest_pos(clean_titles, raw_title):
    highest_score = -1
    res_title = ""
    for title in clean_titles:
        cur_score = compare_titles(title, raw_title)
        if cur_score > highest_score:
            highest_score = cur_score
            res_title = title
    print(highest_score)
    return res_title


def compare_titles(clean_title, raw_title):
    clean_map = dict()
    words = clean_title.split(' ')

    for word in words:
        if word not in clean_map.keys():
            clean_map[word] = 0
        clean_map[word] += 1

    cnt = 0
    raw_words = raw_title.split(" ")
    for raw_word in raw_words:
        if raw_word in clean_map.keys() and clean_map[raw_word] > 0:
            cnt += 1
            clean_map[raw_word] -= 1

    for i in range(0, 3):
        print(i)
    print(i)

    return cnt


start_from_here()
