#include "../include/table_restoration.h"
#include <iostream>
#include <set>

namespace {

/**
 * Cluster coordinates that are within threshold distance
 * Returns averaged cluster centers
 */
std::vector<float> clusterCoordinates(std::vector<float> coords, float threshold) {
    if (coords.empty()) return {};
    
    // Sort coordinates
    std::sort(coords.begin(), coords.end());
    
    std::vector<float> clusters;
    std::vector<float> current_cluster = {coords[0]};
    
    // Group nearby coordinates
    for (size_t i = 1; i < coords.size(); i++) {
        if (coords[i] - current_cluster.back() <= threshold) {
            current_cluster.push_back(coords[i]);
        } else {
            // Average the cluster and start new cluster
            float avg = std::accumulate(current_cluster.begin(), current_cluster.end(), 0.0f) 
                       / current_cluster.size();
            clusters.push_back(avg);
            current_cluster = {coords[i]};
        }
    }
    
    // Add the last cluster
    float avg = std::accumulate(current_cluster.begin(), current_cluster.end(), 0.0f) 
               / current_cluster.size();
    clusters.push_back(avg);
    
    return clusters;
}

/**
 * Find the index of the closest line to the given coordinate
 */
int findClosestLineIndex(const std::vector<float>& lines, float coord) {
    if (lines.empty()) return 0;
    
    int closest_idx = 0;
    float min_dist = std::abs(lines[0] - coord);
    
    for (size_t i = 1; i < lines.size(); i++) {
        float dist = std::abs(lines[i] - coord);
        if (dist < min_dist) {
            min_dist = dist;
            closest_idx = i;
        }
    }
    return closest_idx;
}

/**
 * Ensure table boundaries are included in the line set
 */
void ensureBoundaries(std::vector<float>& lines, float boundary_min, float boundary_max, float threshold) {
    if (lines.empty()) {
        lines.push_back(boundary_min);
        lines.push_back(boundary_max);
        return;
    }
    
    // Add minimum boundary if not present
    if (std::abs(lines.front() - boundary_min) > threshold) {
        lines.insert(lines.begin(), boundary_min);
    } else {
        lines[0] = boundary_min; // Snap to exact boundary
    }
    
    // Add maximum boundary if not present
    if (std::abs(lines.back() - boundary_max) > threshold) {
        lines.push_back(boundary_max);
    } else {
        lines.back() = boundary_max; // Snap to exact boundary
    }
}

} // anonymous namespace

TableStructure restoreTableStructure(
    const std::vector<Box>& cells,
    const Box& table_boundary,
    float cluster_threshold
) {
    TableStructure result;
    
    // Handle empty input
    if (cells.empty()) {
        return result;
    }
    
    // Step 1: Extract all coordinates from cells
    std::vector<float> x_coords, y_coords;
    x_coords.reserve(cells.size() * 2);
    y_coords.reserve(cells.size() * 2);
    
    for (const auto& cell : cells) {
        x_coords.push_back(cell.x1);
        x_coords.push_back(cell.x2);
        y_coords.push_back(cell.y1);
        y_coords.push_back(cell.y2);
    }
    
    // Step 2: Cluster coordinates to get aligned grid lines
    result.col_lines = clusterCoordinates(x_coords, cluster_threshold);
    result.row_lines = clusterCoordinates(y_coords, cluster_threshold);
    
    // Step 3: Ensure table boundaries are included
    ensureBoundaries(result.col_lines, table_boundary.x1, table_boundary.x2, cluster_threshold);
    ensureBoundaries(result.row_lines, table_boundary.y1, table_boundary.y2, cluster_threshold);
    
    // Step 4: Map each cell to the grid
    result.cells.reserve(cells.size());
    
    for (const auto& cell : cells) {
        AlignedCell aligned;
        
        // Find grid positions
        aligned.col_start = findClosestLineIndex(result.col_lines, cell.x1);
        aligned.col_end = findClosestLineIndex(result.col_lines, cell.x2);
        aligned.row_start = findClosestLineIndex(result.row_lines, cell.y1);
        aligned.row_end = findClosestLineIndex(result.row_lines, cell.y2);
        
        // Calculate spans
        aligned.col_span = aligned.col_end - aligned.col_start;
        aligned.row_span = aligned.row_end - aligned.row_start;
        
        // Ensure minimum span of 1
        if (aligned.col_span == 0) {
            aligned.col_end = aligned.col_start + 1;
            aligned.col_span = 1;
        }
        if (aligned.row_span == 0) {
            aligned.row_end = aligned.row_start + 1;
            aligned.row_span = 1;
        }
        
        // Set aligned bounding box from grid lines
        aligned.x1 = result.col_lines[aligned.col_start];
        aligned.x2 = result.col_lines[aligned.col_end];
        aligned.y1 = result.row_lines[aligned.row_start];
        aligned.y2 = result.row_lines[aligned.row_end];
        
        // Preserve confidence score
        aligned.confidence = cell.score;
        
        result.cells.push_back(aligned);
    }
    
    return result;
}
