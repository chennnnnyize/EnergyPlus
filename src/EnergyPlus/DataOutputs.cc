// EnergyPlus, Copyright (c) 1996-2017, The Board of Trustees of the University of Illinois and
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy). All rights
// reserved.
//
// NOTICE: This Software was developed under funding from the U.S. Department of Energy and the
// U.S. Government consequently retains certain rights. As such, the U.S. Government has been
// granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable,
// worldwide license in the Software to reproduce, distribute copies to the public, prepare
// derivative works, and perform publicly and display publicly, and to permit others to do so.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
// (1) Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//
// (2) Redistributions in binary form must reproduce the above copyright notice, this list of
//     conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//
// (3) Neither the name of the University of California, Lawrence Berkeley National Laboratory,
//     the University of Illinois, U.S. Dept. of Energy nor the names of its contributors may be
//     used to endorse or promote products derived from this software without specific prior
//     written permission.
//
// (4) Use of EnergyPlus(TM) Name. If Licensee (i) distributes the software in stand-alone form
//     without changes from the version obtained under this License, or (ii) Licensee makes a
//     reference solely to the software portion of its product, Licensee must refer to the
//     software as "EnergyPlus version X" software, where "X" is the version number Licensee
//     obtained under this License and may not use a different name for the software. Except as
//     specifically required in this Section (4), Licensee shall not use in a company name, a
//     product name, in advertising, publicity, or other promotional activities any name, trade
//     name, trademark, logo, or other designation of "EnergyPlus", "E+", "e+" or confusingly
//     similar designation, without the U.S. Department of Energy's prior written consent.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// ObjexxFCL Headers
#include <ObjexxFCL/string.functions.hh>

// EnergyPlus Headers
#include <DataOutputs.hh>
#include <InputProcessor.hh>
#include "UtilityRoutines.hh"

namespace EnergyPlus {

namespace DataOutputs {

	// Module containing the data and routines dealing with prescanning for
	// requested output variables to limit the number being processed in OutputProcessor
	// Also any input counts (such as autosize counts/records that are used
	// by later program modules.

	// MODULE INFORMATION:
	//       AUTHOR         Linda Lawrie
	//       DATE WRITTEN   July 2010
	//       MODIFIED       April 2011; to include autosize counts
	//       RE-ENGINEERED  na

	// PURPOSE OF THIS MODULE:
	// The module contains structure for output variables that are used in a small number of modules.

	// METHODOLOGY EMPLOYED:
	// na

	// REFERENCES:
	// na

	// OTHER NOTES:
	// na

	// Using/Aliasing

	// Data
	// MODULE PARAMETER DEFINITIONS:
	int const NumMonthlyReports( 62 );
	Array1D_string const MonthlyNamedReports( NumMonthlyReports, { "ZONECOOLINGSUMMARYMONTHLY", "ZONEHEATINGSUMMARYMONTHLY", "ZONEELECTRICSUMMARYMONTHLY", "SPACEGAINSMONTHLY", "PEAKSPACEGAINSMONTHLY", "SPACEGAINCOMPONENTSATCOOLINGPEAKMONTHLY", "ENERGYCONSUMPTIONELECTRICITYNATURALGASMONTHLY", "ENERGYCONSUMPTIONELECTRICITYGENERATEDPROPANEMONTHLY", "ENERGYCONSUMPTIONDIESELFUELOILMONTHLY", "ENERGYCONSUMPTIONDISTRICTHEATINGCOOLINGMONTHLY", "ENERGYCONSUMPTIONCOALGASOLINEMONTHLY", "ENERGYCONSUMPTIONOTHERFUELSMONTHLY", "ENDUSEENERGYCONSUMPTIONELECTRICITYMONTHLY", "ENDUSEENERGYCONSUMPTIONNATURALGASMONTHLY", "ENDUSEENERGYCONSUMPTIONDIESELMONTHLY", "ENDUSEENERGYCONSUMPTIONFUELOILMONTHLY", "ENDUSEENERGYCONSUMPTIONCOALMONTHLY", "ENDUSEENERGYCONSUMPTIONPROPANEMONTHLY", "ENDUSEENERGYCONSUMPTIONGASOLINEMONTHLY", "ENDUSEENERGYCONSUMPTIONOTHERFUELSMONTHLY", "PEAKENERGYENDUSEELECTRICITYPART1MONTHLY", "PEAKENERGYENDUSEELECTRICITYPART2MONTHLY", "ELECTRICCOMPONENTSOFPEAKDEMANDMONTHLY", "PEAKENERGYENDUSENATURALGASMONTHLY", "PEAKENERGYENDUSEDIESELMONTHLY", "PEAKENERGYENDUSEFUELOILMONTHLY", "PEAKENERGYENDUSECOALMONTHLY", "PEAKENERGYENDUSEPROPANEMONTHLY", "PEAKENERGYENDUSEGASOLINEMONTHLY", "PEAKENERGYENDUSEOTHERFUELSMONTHLY", "SETPOINTSNOTMETWITHTEMPERATURESMONTHLY", "COMFORTREPORTSIMPLE55MONTHLY", "UNGLAZEDTRANSPIREDSOLARCOLLECTORSUMMARYMONTHLY", "OCCUPANTCOMFORTDATASUMMARYMONTHLY", "CHILLERREPORTMONTHLY", "TOWERREPORTMONTHLY", "BOILERREPORTMONTHLY", "DXREPORTMONTHLY", "WINDOWREPORTMONTHLY", "WINDOWENERGYREPORTMONTHLY", "WINDOWZONESUMMARYMONTHLY", "WINDOWENERGYZONESUMMARYMONTHLY", "AVERAGEOUTDOORCONDITIONSMONTHLY", "OUTDOORCONDITIONSMAXIMUMDRYBULBMONTHLY", "OUTDOORCONDITIONSMINIMUMDRYBULBMONTHLY", "OUTDOORCONDITIONSMAXIMUMWETBULBMONTHLY", "OUTDOORCONDITIONSMAXIMUMDEWPOINTMONTHLY", "OUTDOORGROUNDCONDITIONSMONTHLY", "WINDOWACREPORTMONTHLY", "WATERHEATERREPORTMONTHLY", "GENERATORREPORTMONTHLY", "DAYLIGHTINGREPORTMONTHLY", "COILREPORTMONTHLY", "PLANTLOOPDEMANDREPORTMONTHLY", "FANREPORTMONTHLY", "PUMPREPORTMONTHLY", "CONDLOOPDEMANDREPORTMONTHLY", "ZONETEMPERATUREOSCILLATIONREPORTMONTHLY", "AIRLOOPSYSTEMENERGYANDWATERUSEMONTHLY", "AIRLOOPSYSTEMCOMPONENTLOADSMONTHLY", "AIRLOOPSYSTEMCOMPONENTENERGYUSEMONTHLY", "MECHANICALVENTILATIONLOADSMONTHLY" } );

	// DERIVED TYPE DEFINITIONS:

	// MODULE VARIABLE DECLARATIONS:
	int MaxConsideredOutputVariables( 0 ); // Max Array size for OutputVariable pre-scanned
	int NumConsideredOutputVariables( 0 ); // Number of variables - pre-scanned, allowed for output
	int iNumberOfRecords; // Number of records in input
	int iNumberOfDefaultedFields; // number of defaulted fields
	int iTotalFieldsWithDefaults; // number of fields that can be defaulted
	int iNumberOfAutoSizedFields; // number of autosized fields
	int iTotalAutoSizableFields; // number of fields that can be autosized
	int iNumberOfAutoCalcedFields; // number of autocalculated fields
	int iTotalAutoCalculatableFields; // number of fields that can be autocalculated

	// Object Data
	// Array1D< OutputReportingVariables > OutputVariablesForSimulation;
	std::unordered_map < std::string, std::unordered_map< std::string, OutputReportingVariables > > OutputVariablesForSimulation;
	// std::unordered_map <std::string, std::tuple< int, RE2, RE2 > > OutputVariablesNames;
	// Functions

	// std::string const key;
	// 	std::string const variableName;
	// 	// std::string const combinedName;
	// 	std::size_t const hashValue;
	// 	bool is_simple_string;

	OutputReportingVariables::OutputReportingVariables(
		std::string const & KeyValue,
		std::string const & VariableName
	) :
		key( KeyValue ),
		variableName( VariableName )
	{
		if ( KeyValue == "*" ) return;
		for ( auto const & c : KeyValue ) {
			if ( c == ' ' || c == '_' || std::isalnum( c ) ) continue;
			is_simple_string = false;
			break;
		}
		if ( is_simple_string ) return;
		pattern = std::unique_ptr< RE2 >( new RE2( KeyValue ) );
		case_insensitive_pattern = std::unique_ptr< RE2 >( new RE2( "(?i)" + KeyValue ) );
		if ( ! pattern->ok() ) {
			ShowSevereError( "Regular expression \"" + KeyValue + "\" for variable name \"" + VariableName + "\" in input file is incorrect" );
			ShowContinueError( pattern->error() );
			ShowFatalError( "Error found in regular expression. Previous error(s) cause program termination." );
		}
	}

	// OutputReportingVariablesBase::OutputReportingVariablesBase(
	// 	std::string const & KeyValue,
	// 	std::string const & VariableName
	// ) :
	// 	key( KeyValue ),
	// 	variableName( VariableName ),
	// 	hashValue( std::hash< std::string >()( KeyValue + VariableName ) )
	// {

	// }

	// Clears the global data in DataOutputs.
	// Needed for unit tests, should not be normally called.
	void
	clear_state()
	{
		MaxConsideredOutputVariables = 0;
		NumConsideredOutputVariables = 0;
		iNumberOfRecords = int();
		iNumberOfDefaultedFields = int();
		iTotalFieldsWithDefaults = int();
		iNumberOfAutoSizedFields = int();
		iTotalAutoSizableFields = int();
		iNumberOfAutoCalcedFields = int();
		iTotalAutoCalculatableFields = int();
		OutputVariablesForSimulation.clear();
		// OutputVariablesNames.clear();
	}

	bool
	FindItemInVariableList(
		std::string const & KeyedValue,
		std::string const & VariableName
	)
	{

		// FUNCTION INFORMATION:
		//       AUTHOR         Linda Lawrie
		//       DATE WRITTEN   July 2010
		//       MODIFIED       December 2016
		//       RE-ENGINEERED  na

		// PURPOSE OF THIS FUNCTION:
		// This function looks up a key and variable name value and determines if they are
		// in the list of required variables for a simulation.

		// OutputReportingVariablesBase reportingPair( KeyedValue, InputProcessor::MakeUPPERCase( VariableName ) );

		// std::string const combinedName( InputProcessor::MakeUPPERCase( KeyedValue + VariableName ) );

		// if ( InputProcessor::MakeUPPERCase( KeyedValue ) == "ENVIRONMENT" ) {
		// 	std::string const test = "";
		// }

		// if ( VariableName == "SITE OUTDOOR AIR DRYBULB TEMPERATURE" ) {
		// 	std::string const test = "";
		// }

		auto const found_variable = OutputVariablesForSimulation.find( InputProcessor::MakeUPPERCase( VariableName ) );
		if ( found_variable == OutputVariablesForSimulation.end() ) return false;

		auto found_key = found_variable->second.find( KeyedValue );
		if ( found_key != found_variable->second.end() ) return true;

		found_key = found_variable->second.find( "*" );
		if ( found_key != found_variable->second.end() ) return true;

		for ( auto it = found_variable->second.begin(); it != found_variable->second.end(); ++it ) {
			if ( it->second.key == "*" ) return true;
//			if ( it->second.is_simple_string ) {
//				if ( equali( KeyedValue, it->second.key ) ) return true;
//			} else {
//				if (
//					RE2::FullMatch( KeyedValue, *it->second.pattern ) || // match against regex as written
//					RE2::FullMatch( KeyedValue, *it->second.case_insensitive_pattern ) // attempt case-insensitive regex comparison
//					)
//				{
//					return true;
//				}
//			}
			if ( equali( KeyedValue, it->second.key ) ) return true;
			if ( it->second.is_simple_string ) continue;
			// if ( equali( KeyedValue, it->second.key ) ) return true;
			// if ( it->second.is_simple_string && equali( KeyedValue, it->second.key ) ) return true;
			// auto const * base = &(*found);
			// auto const * found_cast = dynamic_cast< OutputReportingVariables const * >( base );
			if (
				( it->second.pattern != nullptr && RE2::FullMatch( KeyedValue, *it->second.pattern ) ) || // match against regex as written
				( it->second.case_insensitive_pattern != nullptr && RE2::FullMatch( KeyedValue, *it->second.case_insensitive_pattern ) ) // attempt case-insensitive regex comparison
				)
			{
				return true;
			}
		}

		// for ( auto const & k : found_variable->second ) {
		// 	if ( k.key == "*" ) return true;
		// 	if ( k.is_simple_string && equali( KeyedValue, k.key ) ) return true;
		// 	// auto const * base = &(*found);
		// 	// auto const * found_cast = dynamic_cast< OutputReportingVariables const * >( base );
		// 	if (
		// 		RE2::FullMatch( KeyedValue, *k.pattern ) || // match against regex as written
		// 		RE2::FullMatch( KeyedValue, *k.case_insensitive_pattern ) // attempt case-insensitive regex comparison
		// 		)
		// 	{
		// 		return true;
		// 	}
		// }
		return false;

		// if ( found->second.key == "*" ) return true;
		// if ( found->second.is_simple_string && equali( KeyedValue, found->second.key ) ) return true;
		// // auto const * base = &(*found);
		// // auto const * found_cast = dynamic_cast< OutputReportingVariables const * >( base );
		// if (
		// 	RE2::FullMatch( KeyedValue, *found->second.pattern ) || // match against regex as written
		// 	RE2::FullMatch( KeyedValue, *found->second.case_insensitive_pattern ) // attempt case-insensitive regex comparison
		// 	)
		// {
		// 	return true;
		// }

		// int Found = 0;
		// // std::string LowerCaseVarName;
		// // // case-insensitive search
		// // ConvertCaseToLower( VariableName, LowerCaseVarName);
		// auto const FirstIndex = OutputVariablesNames.find( InputProcessor::MakeUPPERCase( VariableName ) );

		// if ( FirstIndex != OutputVariablesNames.end() ) {
		// 	Found = FirstIndex->second.index;
		// }
		// if ( Found != 0 ) {
		// 	do {
		// 		if ( OutputVariablesForSimulation( Found ).Key == "*" ) {
		// 			return true;
		// 		}

		// 		bool is_simple_string = true;
		// 		for ( auto const & c : KeyValue ) {
		// 			if ( c == ' ' || c == '_' || std::isalnum( c ) ) continue;
		// 			is_simple_string = false;
		// 			break;
		// 		}

		// 		if ( is_simple_string ) {
		// 			if ( equali( KeyedValue, OutputVariablesForSimulation( Found ).Key ) ) {
		// 				return true;
		// 			}
		// 		} else {
		// 			// RE2 pattern( OutputVariablesForSimulation( Found ).Key );
		// 			// if ( ! pattern.ok() ) {
		// 			// 	ShowSevereError( "Regular expression \"" + OutputVariablesForSimulation( Found ).Key + "\" for variable name \"" + VariableName + "\" in input file is incorrect" );
		// 			// 	ShowContinueError( pattern.error() );
		// 			// 	ShowFatalError( "Error found in regular expression. Previous error(s) cause program termination." );
		// 			// 	break;
		// 			// }
		// 			if (
		// 				// equali( KeyedValue, OutputVariablesForSimulation( Found ).Key ) || // straight case-insensitive string comparison
		// 				RE2::FullMatch( KeyedValue, *FirstIndex->second.pattern ) || // match against regex as written
		// 				RE2::FullMatch( KeyedValue, *FirstIndex->second.case_insensitive_pattern ) // attempt case-insensitive regex comparison
		// 				)
		// 			{
		// 				return true;
		// 			}
		// 		}
		// 		Found = OutputVariablesForSimulation( Found ).Next;
		// 	} while ( Found != 0 );
		// }
		// return false;
	}

	// bool
	// FindItemInVariableList(
	// 	std::string const & KeyedValue,
	// 	std::string const & VariableName
	// )
	// {

	// 	// FUNCTION INFORMATION:
	// 	//       AUTHOR         Linda Lawrie
	// 	//       DATE WRITTEN   July 2010
	// 	//       MODIFIED       December 2016
	// 	//       RE-ENGINEERED  na

	// 	// PURPOSE OF THIS FUNCTION:
	// 	// This function looks up a key and variable name value and determines if they are
	// 	// in the list of required variables for a simulation.

	// 	int Found = 0;
	// 	// std::string LowerCaseVarName;
	// 	// // case-insensitive search
	// 	// ConvertCaseToLower( VariableName, LowerCaseVarName);
	// 	auto const FirstIndex = OutputVariablesNames.find( InputProcessor::MakeUPPERCase( VariableName ) );

	// 	if ( FirstIndex != OutputVariablesNames.end() ) {
	// 		Found = FirstIndex->second.index;
	// 	}
	// 	if ( Found != 0 ) {
	// 		do {
	// 			if ( OutputVariablesForSimulation( Found ).Key == "*" ) {
	// 				return true;
	// 			}

	// 			bool is_simple_string = true;
	// 			for ( auto const & c : KeyValue ) {
	// 				if ( c == ' ' || c == '_' || std::isalnum( c ) ) continue;
	// 				is_simple_string = false;
	// 				break;
	// 			}

	// 			if ( is_simple_string ) {
	// 				if ( equali( KeyedValue, OutputVariablesForSimulation( Found ).Key ) ) {
	// 					return true;
	// 				}
	// 			} else {
	// 				// RE2 pattern( OutputVariablesForSimulation( Found ).Key );
	// 				// if ( ! pattern.ok() ) {
	// 				// 	ShowSevereError( "Regular expression \"" + OutputVariablesForSimulation( Found ).Key + "\" for variable name \"" + VariableName + "\" in input file is incorrect" );
	// 				// 	ShowContinueError( pattern.error() );
	// 				// 	ShowFatalError( "Error found in regular expression. Previous error(s) cause program termination." );
	// 				// 	break;
	// 				// }
	// 				if (
	// 					// equali( KeyedValue, OutputVariablesForSimulation( Found ).Key ) || // straight case-insensitive string comparison
	// 					RE2::FullMatch( KeyedValue, *FirstIndex->second.pattern ) || // match against regex as written
	// 					RE2::FullMatch( KeyedValue, *FirstIndex->second.case_insensitive_pattern ) // attempt case-insensitive regex comparison
	// 					)
	// 				{
	// 					return true;
	// 				}
	// 			}
	// 			Found = OutputVariablesForSimulation( Found ).Next;
	// 		} while ( Found != 0 );
	// 	}
	// 	return false;
	// }

} // DataOutputs

} // EnergyPlus
