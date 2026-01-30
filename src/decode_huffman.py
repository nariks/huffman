
import struct
import heapq
import sys

class Node:
    def __init__(self, freq, char=None, left=None, right=None):
        self.freq = freq
        self.char = char
        self.left = left
        self.right = right
        # Tie-breaker: find the minimum ASCII value in this subtree
        self.min_char = char if char is not None else min(left.min_char, right.min_char)

    def __lt__(self, other):
        if self.freq != other.freq:
            return self.freq < other.freq
        return self.min_char < other.min_char

def decompress(input_path):
    base_name = input_path[:-5] if input_path.endswith('.huff') else input_path
    output_path = f"{base_name}_DECODED.txt"

    with open(input_path, 'rb') as f:
        # 1. Read Header
        header = f.read(8)
        if not header: return
        total_chars = struct.unpack('<Q', header)[0]
        
        # Read the 256 frequencies (8 bytes each = 2048 bytes)
        freq_data = f.read(2048)
        if len(freq_data) < 2048:
            print("Error: Incomplete frequency table.")
            return
        freqs = struct.unpack('<' + 'Q' * 256, freq_data)

        # 2. Rebuild Tree
        heap = [Node(freq, char=i) for i, freq in enumerate(freqs) if freq > 0]
        heapq.heapify(heap)

        if not heap:
            print("Error: Empty frequency table.")
            return

        while len(heap) > 1:
            left = heapq.heappop(heap)
            right = heapq.heappop(heap)
            merged = Node(left.freq + right.freq, left=left, right=right)
            heapq.heappush(heap, merged)

        root = heap[0]

        # 3. Decode Bit-stream via Tree Traversal
        # This is significantly faster than string concatenation/lookups
        chars_decoded = 0
        current_node = root
        
        with open(output_path, 'wb') as out:
            while chars_decoded < total_chars:
                byte = f.read(1)
                if not byte: break
                byte_val = ord(byte)

                # Process each bit from MSB to LSB (standard "left-to-right" packing)
                for i in range(7, -1, -1):
                    bit = (byte_val >> i) & 1
                    
                    # Traverse the tree: 0 goes left, 1 goes right
                    current_node = current_node.left if bit == 0 else current_node.right
                    
                    # If we hit a leaf, we found a character
                    if current_node.char is not None:
                        out.write(bytes([current_node.char]))
                        chars_decoded += 1
                        current_node = root # Reset to top for next character
                        
                        if chars_decoded == total_chars:
                            break

    print(f"Successfully decoded {chars_decoded} characters to {output_path}")

if __name__ == "__main__":
    if len(sys.argv) == 2: 
        decompress(sys.argv[1])
    else:
        print("Usage: python decoder.py <file.huff>")
