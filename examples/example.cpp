#include "../include/table_restoration.h"
#include <iostream>
#include <iomanip>

int main() {
    // Test data: 56 cells from real detection results
    std::vector<Box> cells = {
        {456.44f, 268.89f, 615.14f, 287.33f, 0.82f},
        {266.45f, 268.86f, 456.69f, 287.12f, 0.82f},
        {265.27f, 119.50f, 454.09f, 139.63f, 0.82f},
        {457.27f, 287.21f, 616.66f, 305.49f, 0.82f},
        {267.59f, 286.98f, 457.12f, 305.28f, 0.82f},
        {264.04f, 250.25f, 456.26f, 268.88f, 0.82f},
        {453.75f, 119.56f, 613.97f, 139.45f, 0.82f},
        {263.28f, 231.66f, 454.82f, 250.41f, 0.82f},
        {456.03f, 250.16f, 616.44f, 268.84f, 0.81f},
        {256.32f, 92.20f, 453.58f, 119.81f, 0.81f},
        {19.57f, 119.84f, 268.35f, 139.97f, 0.81f},
        {454.63f, 231.52f, 615.49f, 250.24f, 0.81f},
        {19.21f, 268.77f, 274.57f, 287.22f, 0.81f},
        {267.05f, 305.25f, 455.82f, 324.34f, 0.81f},
        {19.46f, 250.16f, 272.71f, 268.78f, 0.81f},
        {453.28f, 92.32f, 614.71f, 119.74f, 0.81f},
        {455.73f, 305.49f, 620.12f, 324.30f, 0.81f},
        {453.81f, 139.34f, 614.48f, 158.31f, 0.80f},
        {19.59f, 287.12f, 274.21f, 305.35f, 0.80f},
        {614.85f, 119.02f, 728.94f, 139.07f, 0.80f},
        {19.18f, 231.92f, 275.26f, 250.37f, 0.80f},
        {616.54f, 287.05f, 729.10f, 305.30f, 0.80f},
        {263.64f, 212.71f, 453.86f, 231.60f, 0.80f},
        {616.59f, 268.65f, 729.54f, 287.05f, 0.80f},
        {617.04f, 249.84f, 729.83f, 268.50f, 0.79f},
        {269.64f, 139.41f, 454.76f, 158.34f, 0.79f},
        {19.97f, 305.24f, 274.73f, 324.25f, 0.79f},
        {454.82f, 324.04f, 621.31f, 344.52f, 0.79f},
        {616.66f, 231.46f, 729.12f, 249.94f, 0.79f},
        {268.94f, 324.02f, 454.84f, 345.19f, 0.79f},
        {264.59f, 194.41f, 455.32f, 212.91f, 0.79f},
        {621.20f, 305.38f, 729.14f, 323.84f, 0.78f},
        {19.73f, 92.72f, 261.12f, 120.11f, 0.78f},
        {19.57f, 139.88f, 270.51f, 158.80f, 0.78f},
        {454.88f, 194.69f, 615.82f, 212.88f, 0.77f},
        {266.20f, 175.42f, 455.25f, 194.50f, 0.77f},
        {20.88f, 323.95f, 274.15f, 346.56f, 0.77f},
        {20.07f, 176.74f, 269.70f, 194.61f, 0.77f},
        {614.91f, 139.02f, 729.68f, 157.92f, 0.77f},
        {614.86f, 60.38f, 727.41f, 91.85f, 0.77f},
        {20.64f, 194.71f, 268.55f, 213.08f, 0.75f},
        {248.24f, 61.15f, 453.89f, 91.44f, 0.75f},
        {453.61f, 61.94f, 613.45f, 91.64f, 0.75f},
        {622.46f, 323.70f, 728.52f, 344.30f, 0.75f},
        {19.93f, 212.89f, 271.63f, 231.74f, 0.73f},
        {454.22f, 212.66f, 615.78f, 231.23f, 0.73f},
        {455.15f, 175.75f, 616.30f, 194.59f, 0.73f},
        {19.67f, 158.92f, 269.28f, 176.87f, 0.69f},
        {613.84f, 92.42f, 728.26f, 119.03f, 0.68f},
        {616.32f, 158.08f, 730.83f, 175.77f, 0.68f},
        {21.63f, 60.20f, 249.90f, 91.47f, 0.66f},
        {616.23f, 175.75f, 730.20f, 194.02f, 0.64f},
        {616.27f, 210.71f, 728.64f, 231.40f, 0.50f},
        {269.68f, 158.29f, 454.27f, 175.95f, 0.47f},
        {455.34f, 158.47f, 615.72f, 175.77f, 0.41f},
        {616.88f, 193.91f, 729.81f, 212.28f, 0.41f}
    };
    
    // Table boundary
    Box table_boundary = {17.13f, 55.46f, 737.41f, 359.02f, 0.98f};
    
    std::cout << "=== Table Structure Restoration Test ===" << std::endl;
    std::cout << "Input: " << cells.size() << " cells" << std::endl;
    std::cout << "Table boundary: [" << table_boundary.x1 << ", " << table_boundary.y1 
              << ", " << table_boundary.x2 << ", " << table_boundary.y2 << "]" << std::endl;
    std::cout << std::endl;
    
    // Run table restoration
    TableStructure table = restoreTableStructure(cells, table_boundary, 2.0f);
    
    // Print grid information
    std::cout << "=== Grid Structure ===" << std::endl;
    std::cout << "Rows: " << table.row_lines.size() << " lines" << std::endl;
    std::cout << "Columns: " << table.col_lines.size() << " lines" << std::endl;
    std::cout << "Grid dimensions: " << (table.row_lines.size() - 1) << " rows × " 
              << (table.col_lines.size() - 1) << " columns" << std::endl;
    std::cout << std::endl;
    
    // Print row lines
    std::cout << "Row lines (y coordinates):" << std::endl;
    for (size_t i = 0; i < table.row_lines.size(); i++) {
        std::cout << "  Row " << i << ": " << std::fixed << std::setprecision(2) 
                  << table.row_lines[i] << std::endl;
    }
    std::cout << std::endl;
    
    // Print column lines
    std::cout << "Column lines (x coordinates):" << std::endl;
    for (size_t i = 0; i < table.col_lines.size(); i++) {
        std::cout << "  Col " << i << ": " << std::fixed << std::setprecision(2) 
                  << table.col_lines[i] << std::endl;
    }
    std::cout << std::endl;
    
    // Print aligned cells
    std::cout << "=== Aligned Cells ===" << std::endl;
    std::cout << "Total cells: " << table.cells.size() << std::endl;
    std::cout << std::endl;
    
    // Count merged cells
    int merged_cell_count = 0;
    for (const auto& cell : table.cells) {
        if (cell.row_span > 1 || cell.col_span > 1) {
            merged_cell_count++;
        }
    }
    std::cout << "Merged cells: " << merged_cell_count << std::endl;
    std::cout << std::endl;
    
    // Print first 10 cells as examples
    std::cout << "Sample cells (first 10):" << std::endl;
    for (size_t i = 0; i < std::min(size_t(10), table.cells.size()); i++) {
        const auto& cell = table.cells[i];
        std::cout << "Cell " << (i + 1) << ":" << std::endl;
        std::cout << "  Grid position: [" << cell.row_start << ":" << cell.row_end 
                  << ", " << cell.col_start << ":" << cell.col_end << "]" << std::endl;
        std::cout << "  Span: " << cell.row_span << " × " << cell.col_span << std::endl;
        std::cout << "  Aligned bbox: [" << std::fixed << std::setprecision(2)
                  << cell.x1 << ", " << cell.y1 << ", " << cell.x2 << ", " << cell.y2 << "]" << std::endl;
        std::cout << "  Confidence: " << cell.confidence << std::endl;
        std::cout << std::endl;
    }
    
    // Print merged cells details
    if (merged_cell_count > 0) {
        std::cout << "=== Merged Cells Details ===" << std::endl;
        int count = 0;
        for (size_t i = 0; i < table.cells.size(); i++) {
            const auto& cell = table.cells[i];
            if (cell.row_span > 1 || cell.col_span > 1) {
                count++;
                std::cout << "Merged cell " << count << " (original cell " << (i + 1) << "):" << std::endl;
                std::cout << "  Position: [" << cell.row_start << ":" << cell.row_end 
                          << ", " << cell.col_start << ":" << cell.col_end << "]" << std::endl;
                std::cout << "  Span: " << cell.row_span << " rows × " << cell.col_span << " cols" << std::endl;
                std::cout << std::endl;
            }
        }
    }
    
    std::cout << "=== Test Complete ===" << std::endl;
    
    return 0;
}
