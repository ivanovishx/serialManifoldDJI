      //TODO: yawRead using RTKData
       while(1){

       RTKData  RTKDataYaw = api->getBroadcastData().rtk;
       std::cout<<"RTKDataYaw.yaw:"<<RTKDataYaw.yaw<<std::endl;
       //////////////
       QuaternionData QYaw = api->getBroadcastData().q; 
       std::cout<<" QuaternionData:"<<"  q0:"<<QYaw.q0<<"  q1:"<<QYaw.q1<<"  q2:"<<QYaw.q2<<"  q3:"<<QYaw.q3<<std::endl;
       //////////////
       CommonData AYaw= api->getBroadcastData().a;
       std::cout<<" CommonData.yaw:"<<" x:"<<AYaw.x<<" y:"<<AYaw.y<<" z:"<<AYaw.z<<std::endl;
       //////////////
       VelocityData VYAW = api->getBroadcastData().v;
       std::cout<<" VelocityData.VYAW:"<<" x:"<<VYAW.x<<" y:"<<VYAW.y<<" z:"<<VYAW.z<<std::endl;
       //////////////
       CommonData WYaw = api->getBroadcastData().w;
       std::cout<<" CommonData.yaw:"<<" x:"<<WYaw.x<<" y:"<<WYaw.y<<" z:"<<WYaw.z<<std::endl;
       //////////////
       PositionData posYaw= api->getBroadcastData().pos;
       std::cout<<" PositionData.yaw:"<<" Lat:"<<posYaw.latitude<<" longitude:"<<posYaw.longitude<<" altitude:"<<posYaw.altitude<<" height:"<<posYaw.height<<" health:"<<posYaw.health<<std::endl;
       //////////////
       MagnetData magYaw = api->getBroadcastData().mag;
       std::cout<<" MagnetData.yaw:"<<" x:"<<magYaw.x<<" y:"<<magYaw.y<<" z:"<<magYaw.z<<std::endl;
       //////////////
       RadioData rcYaw= api->getBroadcastData().rc;
       std::cout<<" RadioData.yaw:"<<rcYaw.yaw<<std::endl;
       //////////////
       FlightStatus statusYaw = api->getBroadcastData().status;
       std::cout<<" FlightStatus.yaw:"<<(int)statusYaw<<std::endl;
       ////////////// 
       // DJI::EulerAngle curEulerYaw = Flight::toEulerAngle(api->getBroadcastData().q).yaw;//Flight::toEulerAngle(api->getBroadcastData().q);
       // DJI::EulerAngle curEuler = Flight::toEulerAngle(api->getBroadcastData().q);
       float curEulerYaw = Flight::toEulerAngle(api->getBroadcastData().q).yaw;//Flight::toEulerAngle(api->getBroadcastData().q);
       // float32_t headingRadYaw = -(curEulerYaw.yaw);
       // float32_t headingYaw = (curEulerYaw.yaw / DEG2RAD);
       std::cout<<" QYaw.q3: "<<QYaw.q3<<" Pi Yaw: "<<(QYaw.q3*3.1416)<<" curEulerYaw: "<<curEulerYaw<<std::endl;
       // std::cout<<" QYaw.q3: "<<QYaw.q3<<" Pi Yaw: "<<(QYaw.q3*3.1416)<<" curEulerYaw: "<<curEulerYaw<<" headingRadYaw: "<<headingRadYaw<<" headingYaw: "<<headingYaw<<" yawDesiredYaw: "<<yawDesiredYaw<<std::endl;
       //////////////
       // CtrlInfoData ctrlYaw = api->getBroadcastData().ctrlInfo;
       // std::cout<<"CtrlInfoData.yaw:"<<ctrlYaw.yaw<<std::endl;
       usleep(1000000);





       }