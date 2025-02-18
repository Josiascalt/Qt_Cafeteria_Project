#pragma once

#include "src/OpenXLSX.hpp"
#include "src/pugixml.hpp"

#include <cmath>
#include <iostream>
#include <string>

bool nowide_status()
{
#ifdef ENABLE_NOWIDE
	return true;
#else
	return false;
#endif
}

static void CreateExcelDoc()
{
    using namespace std;
    using namespace OpenXLSX;

    // load example file
    XLDocument doc;
    doc.create("./Demo09.xlsx", XLForceOverwrite);

    std::string version = "12.345";
    doc.setProperty( XLProperty::AppVersion, version );

    XLCellReference ref("A1");

    uint32_t maxRows = OpenXLSX::MAX_ROWS;
    std::string address = "XFD" + std::to_string( maxRows ); // last allowed column and row
    XLCoordinates coords = XLCellReference::coordinatesFromAddress(address);

    address = "AA";
    uint16_t col = XLCellReference::columnAsNumber(address);
    

    auto const & wsNames = doc.workbook().worksheetNames();

    auto wks = doc.workbook().worksheet( 1 );
    wks.setName( "Worksheet name test");

    // assign some data to row 1 from a vector of strings:
    wks.row(1).values() = std::vector< std::string >{ "column A", "column B", "column C", "column D", "column E", "column F", "column G" };

    auto rng1 = wks.range(XLCellReference("A1"), XLCellReference("I2"));

    XLCell c = wks.cell("A1");   // XLCell move constructor
    XLCell c2 = wks.cell("A1");  // XLCell move constructor
    c2 = c;                      // XLCell copy assignment

    try {
        // manual invocation of XLCell.copyFrom (automatically used by XLCellAssignable copy assignment operator)
        c2.copyFrom( c ); // copyFrom throws on a cell referencing the same XML cell node
        std::cout << "c2 is " << c2 << std::endl;
    }
    catch( XLInputError const & e ) {
        std::cout << "--ERROR: c2.copyFrom( c ) failed: " << e.what() << std::endl;
    }

    int iteration = 0;
    try {
        XLCell c3;
        while( iteration < 2 ) {
            ++iteration;
            c3.copyFrom( wks.cell("A1") ); // copyFrom throws on a cell referencing the same XML cell node
            std::cout << "c3 is " << c3 << std::endl;
        }
    }
    catch( XLInputError const & e ) {
        std::cout << "--ERROR: c3.copyFrom( c ) failed on iteration " << iteration << ": " << e.what() << std::endl;
    }

    // XLCellAssignable ca = wks.cell("A1"); // copy constructor
    XLCellAssignable ca;
    ca = c;                 // XLCellAssignable copy assignment -> refers to "A1"
    ca = wks.cell("B1");    // XLCellAssignable move assignment -> assigns contents of "B1" to "A1"
    XLCell x = ca;          // XLCell copy assignment


    wks.cell("A25" ).value() = "42";      // value assignment of any type
    wks.cell("A25" ).formula() = "=4+3";  // formula assignment from string
    wks.cell("C11") = wks.cell("A25");    // copy assignment of all cell contents (like copy & paste in Excel)
    wks.cell("D12") = wks.cell("A1");
    wks.cell("D12") = wks.cell("C11");

    // copy some cell contents around (value, attributes & formula):
    wks.cell("D13") = wks.cell("C11");
    wks.cell("D13") = wks.cell("A1");
    XLCellValue D13 = wks.cell("D13").value();
   
    wks.column( 3 ).setWidth( 1 );

    // wks.row(2).values() = std::vector<int> { 1, 2, 3, 4, 5, 6, 7, 8 };
    wks.row(2).values() = std::vector<bool> { true, true, false, false, true, false, true };

    std::list< XLCellValue > l2;
    for( int i = 0; i < 10; ++i ) {
        l2.push_back( std::move( XLCellValue(i) ) );
    }
    wks.row(3).values() = l2; // assign a std::list of values to a worksheet row
    // wks.row(3).values() = wks.row(2).cells();

    std::vector< XLCellValue > vec1 = wks.row(1).values(); // get row values as a std::vector of XLCellValue


    std::vector< XLCellValue > vec2;
    vec2 = wks.row(4).values();

    wks.row(4).values() = vec1; // assign a std::vector of XLCellValue to row values

    vec2 = wks.row(4).values();
    
    XLCellValue B3 = wks.cell("B3").value();

    XLCellValue G2 = wks.cell("G2").value();

    XLCellValue G1 = wks.cell("G1").value();
    std::string vG1 = "";
    try {
        vG1 = G1.get< std::string >();
    }
    catch( ... ) {
        //std::cout << "failed to G1.get< std::string >(), attempting the new std::visit getString..." << std::endl;
        vG1 = G1.getString();
    }
    std::string sG1 = G1.typeAsString();
    XLCellValue A1 = wks.cell("A1").value();
    XLCellValue B1 = wks.cell("B1").value();
    XLCellValue C1 = wks.cell("C1").value();
    XLCellValue D1 = wks.cell("D1").value();
    XLCellValue E1 = wks.cell("E1").value();
    XLCellValue F1 = wks.cell("F1").value();
    XLCellValue Z35 = wks.cell("Z35").value();

    A1 = wks.cell("A35").value();

   
    std::string newSheetName;
    newSheetName = "Sheet2"; if( !doc.workbook().sheetExists( newSheetName ) ) doc.workbook().addWorksheet( newSheetName );
    auto wks2 = doc.workbook().worksheet( newSheetName );
    newSheetName = "Sheet3"; if( !doc.workbook().sheetExists( newSheetName ) ) doc.workbook().addWorksheet( newSheetName );
    auto wks3 = doc.workbook().worksheet( newSheetName );

    for( int sheetIndex = 1; sheetIndex <= 3; ++sheetIndex ) {
        doc.workbook().sheet( sheetIndex ).setSelected(false);
        doc.workbook().sheet( sheetIndex ).setVisibility(XLSheetState::Visible);
    }

    wks.setActive();
    wks2.setActive();
    wks3.setActive();
 
    // XLSheetState::Visible, XLSheetState::Hidden, XLSheetState::VeryHidden
    // wks.setVisibility( XLSheetState::Visible );
 
    wks2.setVisibility( XLSheetState::VeryHidden );

    doc.workbook().setSheetIndex( "Sheet3", 2 );
    // How to get a sheet type from the shared sheet index (indexes both worksheets and chartsheets)
    for( int sheetIndex = 1; sheetIndex <= 3; ++sheetIndex ) {
        auto sheetType = doc.workbook().typeOfSheet( sheetIndex );
        std::string sheetTypeString = "(unknown)";
        if( sheetType == XLSheetType::Worksheet ) sheetTypeString = "Worksheet";
        else if( sheetType == XLSheetType::Chartsheet ) sheetTypeString = "Chartsheet";
    }

    doc.save();    // implies XLForceOverwrite
    doc.close();
}
