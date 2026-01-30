#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void generate_output_path(const char* input, char* output, size_t max_len) {
    // 1. Copy the entire input path to the output buffer
    // We leave room for the 5 characters in ".huff" plus the null terminator
    strncpy(output, input, max_len - 6);
    output[max_len - 6] = '\0'; // Safety null-termination

    // 2. Simply append ".huff" to the end
    // This keeps the original extension (e.g., .png or .txt) intact
    strcat(output, ".huff");
}

void generate_decoded_path(const char* input, char* output, size_t max_len) {
    // 1. Copy input to output buffer safely
    strncpy(output, input, max_len - 1);
    output[max_len - 1] = '\0';

    // 2. Find ".huff" and remove it
    char *huff_ext = strstr(output, ".huff");
    if (huff_ext) {
        *huff_ext = '\0';

        // 3. Find the original extension (e.g., the '.' in image.png)
        char *orig_ext = strrchr(output, '.');
        if (orig_ext) {
            char suffix[16];
            strncpy(suffix, orig_ext, sizeof(suffix) - 1);
            suffix[sizeof(suffix) - 1] = '\0';

            *orig_ext = '\0'; // Remove original extension temporarily
            strncat(output, "_decoded", max_len - strlen(output) - 1);
            strncat(output, suffix, max_len - strlen(output) - 1);
        } else {
            // No original extension found (e.g., file was just named 'data.huff')
            strncat(output, "_decoded", max_len - strlen(output) - 1);
        }
    } else {
        // Fallback if file doesn't end in .huff
        strncat(output, "_decoded", max_len - strlen(output) - 1);
    }
}

/**
 * Reports the efficiency of the compression using standard industry metrics.
 */
void print_stats(const char* input, const char* output) {
    struct stat st_in, st_out;
    
    if (stat(input, &st_in) == 0 && stat(output, &st_out) == 0) {
        // Space Savings: Percentage of the original file that was removed.
        double space_savings = (st_in.st_size > 0) 
            ? (1.0 - ((double)st_out.st_size / st_in.st_size)) * 100.0 : 0;
            
        // Compression Ratio: The factor of reduction (Original Size / Compressed Size).
        double compression_ratio = (st_out.st_size > 0) 
            ? (double)st_in.st_size / st_out.st_size : 1.0;
        
        printf("\n=== Compression Performance ===\n");
        printf("Original Size:      %lld bytes\n", (long long)st_in.st_size);
        printf("Compressed Size:    %lld bytes\n", (long long)st_out.st_size);
        printf("Compression Ratio:  %.2fx\n", compression_ratio);
        printf("Space Savings:      %.2f%%\n", space_savings);
        printf("================================\n");
    } else {
        perror("Error calculating compression stats");
    }
}

/**
 * Recursively traverses the Huffman tree to print the bit-codes for each character.
 */
void print_huffman_codes(HuffmanNode *root, char *path, int depth) {
    if (!root) return;

    // Leaf node: We've reached a character
    if (!root->left && !root->right) {
        path[depth] = '\0';
        
        // Output formatting: Hex, Char, Frequency, and the Bit String
        // Determine if character is printable, otherwise show a dot
        char display_char = (root->value >= 32 && root->value <= 126) ? (char)root->value : '.';

        // Print in a structured, column-aligned format
        printf("0x%02X | '%c' | Freq: %-10llu | Code: %s\n", 
            root->value, 
            display_char, 
            (unsigned long long)root->freq, 
            path);
        return;
    }

    // Standard recursive walk: Left is 0, Right is 1
    if (root->left) {
        path[depth] = '0';
        print_huffman_codes(root->left, path, depth + 1);
    }
    
    if (root->right) {
        path[depth] = '1';
        print_huffman_codes(root->right, path, depth + 1);
    }
}
