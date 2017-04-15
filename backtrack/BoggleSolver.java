// https://www.cs.duke.edu/courses/cps100/fall12/Recitations/Recitation11.html

public class BoggleSolver {

    private static BufferedReader in = null;
    private static final String INPUT_FILE = "dictionary.txt";

    public static void beginFileReader() {
        try {
            in = new BufferedReader(new FileReader(new File(BoggleSolver.class
                    .getResource(INPUT_FILE).toURI())));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }

    private Trie buildTrie() {
        Trie trie = new Trie();
        beginFileReader();
        String line = null;
        try {
            while ((line = in.readLine()) != null) {
                String[] words = line.split(" ");
                for (String word : words) {
                    word = word.trim().toLowerCase();
                    trie.addWord(word);
                }
            }
            if (in != null) {
                in.close();
            }
        } catch (IOException e1) {
            e1.printStackTrace();
        }
        return trie;
    }

    public Set<String> findWords(char[][] map, Trie dict) {
        Set<String> ans = new TreeSet<String>();
        int m = map.length;
        int n = map[0].length;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                boolean[][] visited = new boolean[m][n];
                findWordsDfs(ans, dict, map, visited, new Item(i, j, ""));
                // item have 3 parameters:
                // location x,y and the prefix string before reaching (i.j)
            }
        }
        return ans;
    }

    public void findWordsDfs(Set<String> ans, Trie dict, char[][] map,
            boolean[][] visited, Item item) {
        // item: the location that we're going to test
        // item.prefix is the word prefix before reaching (x, y)

        int m = map.length;
        int n = map[0].length;
        int x = item.x;
        int y = item.y;

        // check whether cur.(x,y) is a valid position
        if (x < 0 || x >= m || y < 0 || y >= n) {
            return;
        } else if (visited[x][y]) {
            return;
        }
        String newWord = item.prefix + map[x][y];
        // check whether cur.prefix is a valid prefix
        TrieNode findWord = dict.match(newWord);
        if (findWord == null) {
            // up to this position (x, y), the word dont' exists
            return;
        }
        // now cur is in a valid position, with a valid prefix
        if (findWord.isWord()) {
            ans.add(newWord);
        }
        // visit this position, and continue in 4 different directions
        visited[x][y] = true;
        findWordsDfs(ans, dict, map, visited, new Item(x, y - 1, newWord));
        findWordsDfs(ans, dict, map, visited, new Item(x, y + 1, newWord));
        findWordsDfs(ans, dict, map, visited, new Item(x - 1, y, newWord));
        findWordsDfs(ans, dict, map, visited, new Item(x + 1, y, newWord));
        visited[x][y] = false;
    }

    public static void main(String[] args) {
        String[] rows = "eela,elps,weut,korn".split(",");
        char[][] input = new char[4][4];
        for (int i = 0; i < 4; i++) {
            input[i] = rows[i].toCharArray();
        }

        // prepare test data
        BoggleSolver solver = new BoggleSolver();
        Trie dictionary = solver.buildTrie();
        // start finding words
        Set<String> set = solver.findWords(input, dictionary);
        // present the result
        System.out.println(set.size() + " words are found, they are: ");
        for (String str : set) {
            System.out.println(str);
        }
    }

    class Item {
        public final int x, y;
        public final String prefix;

        public Item(int row, int column, String prefix) {
            this.x = row;
            this.y = column;
            this.prefix = prefix;
        }
    }
}