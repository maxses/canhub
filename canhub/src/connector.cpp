/**---------------------------------------------------------------------------
 *
 * @file       connector.cpp
 * @brief      Class for a connector
 *
 *             See class documentation.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Header ----------------------------------------------------------------*/


#include <canhub/connector.hpp>


/*--- Implementation --------------------------------------------------------*/


namespace CANHub
{


CConnector::CConnector( QObject *parent )
   :QObject(parent)
{
}


CConnector::~CConnector()
{
}


} // namespace CANHub


/*--- fin -------------------------------------------------------------------*/
