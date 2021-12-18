clc;
dhparams = [0   	-pi/2   0.0785	0;
            0.16474   	 0      0       pi/2;
            0.16474	 0      0		0;
            0.0145	pi/2	-0.049		0;
            0.029   pi/2	0.049   	0;
            0       0       0.021       0];

robot = rigidBodyTree;

body1 = rigidBody('b1');
jnt1 = rigidBodyJoint('jnt1','revolute');
body2 = rigidBody('b2');
jnt2 = rigidBodyJoint('jnt2','revolute');
jnt2.HomePosition = -pi/2;
body3 = rigidBody('b3');
jnt3 = rigidBodyJoint('jnt3','revolute');
jnt3.HomePosition = pi/2;
body4 = rigidBody('b4');
jnt4 = rigidBodyJoint('jnt4','revolute');
body5 = rigidBody('b5');
jnt5 = rigidBodyJoint('jnt5','revolute');
tool = rigidBody('b6');
jnt6 = rigidBodyJoint('jnt6','revolute');
setFixedTransform(jnt1,dhparams(1,:),'dh');
setFixedTransform(jnt2,dhparams(2,:),'dh');
setFixedTransform(jnt3,dhparams(3,:),'dh');
setFixedTransform(jnt4,dhparams(4,:),'dh');
setFixedTransform(jnt5,dhparams(5,:),'dh');
setFixedTransform(jnt6,dhparams(6,:),'dh');
body1.Joint = jnt1;
body2.Joint = jnt2;
body3.Joint = jnt3;
body4.Joint = jnt4;
body5.Joint = jnt5;
tool.Joint = jnt6;
basename = robot.BaseName;
addBody(robot,body1,basename);
addBody(robot,body2,'b1');
addBody(robot,body3,'b2');
addBody(robot,body4,'b3');
addBody(robot,body5,'b4');
addBody(robot,tool,'b5');
%showdetails(robot)
show(robot)