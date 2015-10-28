// -*- C++ -*-
/*!
 * @file  VelocityController.cpp
 * @brief Velocity Controller
 * @date $Date$
 *
 * $Id$
 */

#include "VelocityController.h"

// Module specification
// <rtc-template block="module_spec">
static const char* velocitycontroller_spec[] =
  {
    "implementation_id", "VelocityController",
    "type_name",         "VelocityController",
    "description",       "Velocity Controller",
    "version",           "1.0.0",
    "vendor",            "yumin05cim",
    "category",          "Tes",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
VelocityController::VelocityController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_velocity1In("velocity1", m_velocity1),
    m_velocity2In("velocity2", m_velocity2),
    m_sumVelocityOut("sumVelocity", m_sumVelocity)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
VelocityController::~VelocityController()
{
}



RTC::ReturnCode_t VelocityController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("velocity1", m_velocity1In);
  addInPort("velocity2", m_velocity2In);
  
  // Set OutPort buffer
  addOutPort("sumVelocity", m_sumVelocityOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t VelocityController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t VelocityController::onActivated(RTC::UniqueId ec_id)
{
	double velocity1_vx = 0.0;
	double velocity1_vy = 0.0;
	double velocity1_va = 0.0;

	double velocity2_vx = 0.0;
	double velocity2_vy = 0.0;
	double velocity2_va = 0.0;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t VelocityController::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t VelocityController::onExecute(RTC::UniqueId ec_id)
{
	if(this->m_velocity1In.isNew() || this->m_velocity2In.isNew()) {

	m_velocity1In.read();
	m_velocity2In.read();

	//Velocity Data from Obstacle Avoidance
	double velocity1_vx = m_velocity1.data.vx;
	double velocity1_vy = m_velocity1.data.vy;
	double velocity1_va = m_velocity1.data.va;

	//Velocity Data from Audio Command
	double velocity2_vx = m_velocity2.data.vx;
	double velocity2_vy = m_velocity2.data.vy;
	double velocity2_va = m_velocity2.data.va;

	if(velocity1_vx == 0){	//NO_OBSTACLE
		m_sumVelocity.data.vx = velocity2_vx;
		m_sumVelocity.data.vy = velocity2_vy;
		m_sumVelocity.data.va = velocity2_va;
	}else{	//ANY_OBSTACLE
		m_sumVelocity.data.vx = velocity1_vx;
		m_sumVelocity.data.vy = velocity1_vy;
		m_sumVelocity.data.va = velocity1_va;
	}
/*
	m_sumVelocity.data.vx = velocity1_vx + velocity2_vx;
	m_sumVelocity.data.vy = velocity1_vy + velocity2_vy;
	m_sumVelocity.data.va = velocity1_va + velocity2_va;
*/
	std::cout <<  "vx = " << m_sumVelocity.data.vx << ", ";
	std::cout <<  "vy = " << m_sumVelocity.data.vy << ", ";
	std::cout <<  "va = " << m_sumVelocity.data.va << std::endl;

	m_sumVelocityOut.write();
	
	}

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t VelocityController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t VelocityController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void VelocityControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(velocitycontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<VelocityController>,
                             RTC::Delete<VelocityController>);
  }
  
};


