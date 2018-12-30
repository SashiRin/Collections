package main.java._OA.Amazon;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class KSubstring {
    // O(n) sliding window non-repeated results
    public int kSubstring(String s, int K) {
        int i = 0, j = 0, len = s.length();
        if (K == 0) {
            return 0;
        }
        boolean[] set = new boolean[256];
        Set<String> res = new HashSet<>();
        while (i < len && j < len) {
            while (j < len && !set[s.charAt(j)] && j - i + 1 <= K) {
                set[s.charAt(j++)] = true;
            }
            if (j - i + 1 > K) res.add(s.substring(i, j));
            set[s.charAt(i++)] = false;
        }
        return res.size();
    }

    // O(n*n) -- repeated
    int countkDist(String str, int k) {
        int res = 0;
        int n = str.length();
        int cnt[] = new int[26];

        if (k == 0) {
            return 0;
        }

        for (int i = 0; i < n; i++) {
            int dist_count = 0;

            Arrays.fill(cnt, 0);

            for (int j = i; j < n; j++) {
                if (cnt[str.charAt(j) - 'a'] == 0) {
                    dist_count++;
                }

                cnt[str.charAt(j) - 'a']++;
                if (dist_count == k)
                    res++;
            }
        }

        return res;
    }
}
