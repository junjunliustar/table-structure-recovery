# Table Structure Recovery

A comprehensive library for recovering and analyzing table structures from various document formats, including PDFs, images, and HTML documents.

## Features

- **Multi-format Support**: Process tables from PDF documents, images (PNG, JPG, TIFF), and HTML files
- **Intelligent Structure Detection**: Advanced algorithms to detect table boundaries, rows, columns, and cell structures
- **Cell Merging Detection**: Automatically identifies and handles merged cells (both horizontal and vertical spans)
- **Text Extraction**: Extracts text content from table cells with high accuracy
- **Multiple Output Formats**: Export recovered tables to CSV, JSON, Excel, HTML, and Markdown
- **OCR Integration**: Built-in OCR support for image-based tables using Tesseract
- **Border Detection**: Robust algorithms for detecting table borders and gridlines
- **Borderless Table Support**: Handles tables without explicit borders using text alignment analysis
- **Batch Processing**: Process multiple documents in parallel for improved performance
- **Quality Metrics**: Provides confidence scores and quality metrics for recovery results

## Algorithm Overview

### Table Detection Pipeline

The library employs a multi-stage pipeline for table structure recovery:

1. **Document Preprocessing**
   - Image enhancement and noise reduction
   - Deskewing and orientation correction
   - Binarization for optimal contrast

2. **Table Region Detection**
   - Edge detection using Canny and Hough transforms
   - Contour analysis for table boundary identification
   - Machine learning-based region classification

3. **Structure Analysis**
   - Line detection for grid identification
   - Whitespace analysis for borderless tables
   - Cell clustering using DBSCAN algorithm
   - Row and column alignment detection

4. **Cell Content Extraction**
   - OCR for text recognition (when needed)
   - Text block segmentation
   - Font and style preservation

5. **Post-processing**
   - Cell relationship mapping
   - Merge detection and span calculation
   - Data validation and correction

### Key Algorithms

- **Adaptive Line Detection**: Combines Hough Line Transform with adaptive thresholding
- **Cell Graph Construction**: Builds a graph representation of table cells for relationship mapping
- **Span Resolution**: Uses constraint satisfaction to resolve complex cell spanning patterns
- **Text Alignment Analysis**: Statistical methods to infer structure from text positioning

## Installation

### Prerequisites

- Python 3.8 or higher
- pip package manager

### Basic Installation

```bash
pip install table-structure-recovery
```

### Installation with All Dependencies

```bash
pip install table-structure-recovery[full]
```

### Development Installation

```bash
git clone https://github.com/junjunliustar/table-structure-recovery.git
cd table-structure-recovery
pip install -e ".[dev]"
```

### Additional Requirements

For OCR functionality, install Tesseract:

**Ubuntu/Debian:**
```bash
sudo apt-get install tesseract-ocr
```

**macOS:**
```bash
brew install tesseract
```

**Windows:**
Download and install from [GitHub Tesseract Releases](https://github.com/UB-Mannheim/tesseract/wiki)

## Usage Examples

### Basic Table Extraction

```python
from table_structure_recovery import TableRecovery

# Initialize the recovery engine
recovery = TableRecovery()

# Extract tables from a PDF document
tables = recovery.extract_from_pdf("document.pdf")

# Process the first table
table = tables[0]
print(f"Detected {table.rows} rows and {table.cols} columns")

# Export to CSV
table.to_csv("output.csv")
```

### Image-based Table Recovery

```python
from table_structure_recovery import TableRecovery

# Initialize with OCR enabled
recovery = TableRecovery(use_ocr=True, ocr_lang='eng')

# Extract from image
tables = recovery.extract_from_image("table_image.png")

# Export to multiple formats
for i, table in enumerate(tables):
    table.to_csv(f"table_{i}.csv")
    table.to_json(f"table_{i}.json")
    table.to_excel(f"table_{i}.xlsx")
```

### Advanced Configuration

```python
from table_structure_recovery import TableRecovery, Config

# Custom configuration
config = Config(
    min_table_confidence=0.85,
    detect_borderless=True,
    merge_detection=True,
    parallel_processing=True,
    max_workers=4
)

recovery = TableRecovery(config=config)

# Extract with detailed metrics
tables = recovery.extract_from_pdf(
    "document.pdf",
    return_metrics=True
)

for table in tables:
    print(f"Confidence: {table.confidence:.2f}")
    print(f"Quality Score: {table.quality_score:.2f}")
    print(f"Cell Count: {table.cell_count}")
```

### Batch Processing

```python
from table_structure_recovery import BatchProcessor
from pathlib import Path

# Initialize batch processor
processor = BatchProcessor(num_workers=4)

# Process all PDFs in a directory
input_dir = Path("input_documents")
output_dir = Path("output_tables")

results = processor.process_directory(
    input_dir,
    output_dir,
    file_pattern="*.pdf",
    output_format="csv"
)

# Check results
for result in results:
    print(f"{result.filename}: {result.table_count} tables extracted")
```

### Working with Table Objects

```python
# Access table data
table = tables[0]

# Get cell value
value = table.get_cell(row=0, col=0)

# Get row data
row_data = table.get_row(0)

# Get column data
col_data = table.get_column(0)

# Iterate over cells
for row in range(table.rows):
    for col in range(table.cols):
        cell = table.get_cell(row, col)
        print(f"({row},{col}): {cell.text}")

# Check for merged cells
if table.has_merged_cells():
    for merge in table.get_merged_cells():
        print(f"Merged region: {merge.start_row}-{merge.end_row}, "
              f"{merge.start_col}-{merge.end_col}")
```

### Custom Processing Pipeline

```python
from table_structure_recovery import (
    TableRecovery,
    preprocessors,
    detectors,
    extractors
)

# Build custom pipeline
recovery = TableRecovery()

# Add custom preprocessing steps
recovery.add_preprocessor(preprocessors.DeskewCorrection())
recovery.add_preprocessor(preprocessors.NoiseReduction(level=2))

# Use specific detector
recovery.set_detector(detectors.BorderBasedDetector(
    min_line_length=50,
    line_gap_tolerance=5
))

# Configure extractor
recovery.set_extractor(extractors.OCRExtractor(
    engine='tesseract',
    languages=['eng', 'fra'],
    confidence_threshold=0.7
))

# Process document
tables = recovery.extract_from_pdf("document.pdf")
```

## API Reference

### TableRecovery Class

Main class for table structure recovery operations.

#### Methods

- `extract_from_pdf(file_path, pages=None, return_metrics=False)`
- `extract_from_image(file_path, return_metrics=False)`
- `extract_from_html(file_path, return_metrics=False)`
- `extract_from_url(url, return_metrics=False)`

### Table Class

Represents a recovered table structure.

#### Properties

- `rows`: Number of rows
- `cols`: Number of columns
- `confidence`: Detection confidence score (0-1)
- `quality_score`: Overall quality metric (0-1)
- `has_header`: Boolean indicating header presence

#### Methods

- `get_cell(row, col)`: Get cell at position
- `get_row(row_index)`: Get entire row
- `get_column(col_index)`: Get entire column
- `to_csv(file_path, **kwargs)`: Export to CSV
- `to_json(file_path, **kwargs)`: Export to JSON
- `to_excel(file_path, **kwargs)`: Export to Excel
- `to_html(file_path, **kwargs)`: Export to HTML
- `to_markdown(file_path, **kwargs)`: Export to Markdown
- `to_dataframe()`: Convert to pandas DataFrame

### Config Class

Configuration options for table recovery.

#### Parameters

- `min_table_confidence` (float): Minimum confidence threshold (default: 0.7)
- `detect_borderless` (bool): Enable borderless table detection (default: True)
- `merge_detection` (bool): Enable merged cell detection (default: True)
- `parallel_processing` (bool): Enable parallel processing (default: False)
- `max_workers` (int): Maximum worker threads (default: None)
- `ocr_enabled` (bool): Enable OCR (default: False)
- `ocr_language` (str): OCR language code (default: 'eng')

## Project Structure

```
table-structure-recovery/
├── src/
│   ├── table_structure_recovery/
│   │   ├── __init__.py
│   │   ├── core/
│   │   │   ├── __init__.py
│   │   │   ├── recovery.py          # Main recovery engine
│   │   │   ├── table.py              # Table data structure
│   │   │   ├── cell.py               # Cell representation
│   │   │   └── config.py             # Configuration management
│   │   ├── detection/
│   │   │   ├── __init__.py
│   │   │   ├── border_detector.py    # Border-based detection
│   │   │   ├── borderless_detector.py # Borderless detection
│   │   │   ├── line_detector.py      # Line detection algorithms
│   │   │   └── region_detector.py    # Table region detection
│   │   ├── extraction/
│   │   │   ├── __init__.py
│   │   │   ├── ocr_extractor.py      # OCR-based extraction
│   │   │   ├── text_extractor.py     # Text extraction
│   │   │   └── pdf_extractor.py      # PDF-specific extraction
│   │   ├── preprocessing/
│   │   │   ├── __init__.py
│   │   │   ├── image_processor.py    # Image preprocessing
│   │   │   ├── deskew.py             # Deskewing algorithms
│   │   │   └── enhancement.py        # Image enhancement
│   │   ├── postprocessing/
│   │   │   ├── __init__.py
│   │   │   ├── merge_resolver.py     # Cell merge resolution
│   │   │   ├── validator.py          # Result validation
│   │   │   └── corrector.py          # Error correction
│   │   ├── exporters/
│   │   │   ├── __init__.py
│   │   │   ├── csv_exporter.py
│   │   │   ├── json_exporter.py
│   │   │   ├── excel_exporter.py
│   │   │   ├── html_exporter.py
│   │   │   └── markdown_exporter.py
│   │   └── utils/
│   │       ├── __init__.py
│   │       ├── geometry.py           # Geometric utilities
│   │       ├── image_utils.py        # Image utilities
│   │       └── metrics.py            # Quality metrics
├── tests/
│   ├── unit/
│   ├── integration/
│   └── fixtures/
├── docs/
│   ├── api/
│   ├── tutorials/
│   └── examples/
├── examples/
│   ├── basic_usage.py
│   ├── advanced_config.py
│   └── batch_processing.py
├── requirements.txt
├── setup.py
├── README.md
├── LICENSE
└── CONTRIBUTING.md
```

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Development Setup

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/table-structure-recovery.git`
3. Create a virtual environment: `python -m venv venv`
4. Activate it: `source venv/bin/activate` (Linux/Mac) or `venv\Scripts\activate` (Windows)
5. Install dev dependencies: `pip install -e ".[dev]"`
6. Run tests: `pytest`

## Testing

```bash
# Run all tests
pytest

# Run with coverage
pytest --cov=table_structure_recovery

# Run specific test file
pytest tests/unit/test_recovery.py

# Run with verbose output
pytest -v
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Citation

If you use this library in your research, please cite:

```bibtex
@software{table_structure_recovery,
  author = {Liu, Junjun},
  title = {Table Structure Recovery: A Comprehensive Library for Table Analysis},
  year = {2025},
  url = {https://github.com/junjunliustar/table-structure-recovery}
}
```

## Acknowledgments

- Built with OpenCV, Tesseract OCR, and PyPDF2
- Inspired by research in document analysis and table understanding
- Thanks to all contributors and users for feedback and improvements

## Support

- **Issues**: [GitHub Issues](https://github.com/junjunliustar/table-structure-recovery/issues)
- **Discussions**: [GitHub Discussions](https://github.com/junjunliustar/table-structure-recovery/discussions)
- **Email**: For private inquiries, contact the maintainer

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for version history and updates.

---

**Last Updated**: 2025-12-16

**Version**: 1.0.0

**Status**: Active Development
