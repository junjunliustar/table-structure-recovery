#ifndef TABLE_RESTORATION_H
#define TABLE_RESTORATION_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

// Input box structure
struct Box {
    float x1, y1, x2, y2;
    float score;
};

// Output aligned cell structure
struct AlignedCell {
    float x1, y1, x2, y2;           // Aligned bounding box
    int row_start, row_end;          // Grid row range [row_start, row_end)
    int col_start, col_end;          // Grid column range [col_start, col_end)
    int row_span, col_span;          // Span dimensions
    float confidence;                // Original detection score
};

// Output table structure
struct TableStructure {
    std::vector<float> row_lines;    // Horizontal grid lines (y coordinates)
    std::vector<float> col_lines;    // Vertical grid lines (x coordinates)
    std::vector<AlignedCell> cells;  // All aligned cells
};

/**
 * Restore table structure from detected cells
 * 
 * @param cells Detected cell bounding boxes
 * @param table_boundary Table boundary box
 * @param cluster_threshold Distance threshold for coordinate clustering (default: 2.0)
 * @return TableStructure with aligned cells and grid information
 */
TableStructure restoreTableStructure(
    const std::vector<Box>& cells,
    const Box& table_boundary,
    float cluster_threshold = 2.0
);

#endif // TABLE_RESTORATION_H
