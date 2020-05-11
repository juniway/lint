public class Trie {
    private TrieNode root;

    public Trie() {
        this.root = new TrieNode();
    }

    public void addWord(String word) {
        TrieNode node = this.root;
        for (char c : word.toCharArray()) {
            node = node.addChild(c);
            if (node == null)
                return;
        }
        node.setWord(true);
    }

    public TrieNode match(String s) {
        TrieNode node = this.root;
        for (char c : s.toCharArray()) {
            node = node.get(c);
            if (node == null)
                return null;
        }
        return node;
    }
}