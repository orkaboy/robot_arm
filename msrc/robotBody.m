clc;clear;
addpath(genpath("3Dmodels/LowPoly"));
dhparams = [0   	-pi/2   0	0;
            0.16474   	 0      0       pi/2;
            0.16474	 0      0		0;
            0.0145	pi/2	-0.049		0;
            0.0145   pi/2	0.049   	0;
            0       0       0.021       0];
        %0.0785       
        
robot = rigidBodyTree;
body1 = rigidBody('b1');
addVisual(body1,"Mesh",'LP_first_joint.stl');
jnt1 = rigidBodyJoint('jnt1','revolute');
body2 = rigidBody('b2');
addVisual(body2,"Mesh",'LP_first_arm.stl');
jnt2 = rigidBodyJoint('jnt2','revolute');
jnt2.HomePosition = -pi/2;
body3 = rigidBody('b3');
addVisual(body3,"Mesh",'LP_second_arm.stl');
jnt3 = rigidBodyJoint('jnt3','revolute');
jnt3.HomePosition = pi/2;
body4 = rigidBody('b4');
addVisual(body4,"Mesh","LP_first_connector.stl");
jnt4 = rigidBodyJoint('jnt4','revolute');
jnt4.HomePosition = pi/2;
body5 = rigidBody('b5');
addVisual(body5,"Mesh","LP_second_connector.stl");
jnt5 = rigidBodyJoint('jnt5','revolute');
jnt5.HomePosition = pi/2;
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
config = homeConfiguration(robot);

show(robot,config)
hold on

endEffT = getTransform(robot,config,'b1','b5')
pointA = [-endEffT(2,4), - endEffT(1,4), endEffT(3,4)];

pointB = pointA + [0,0.3,0];

tic
invKinModel = generalizedInverseKinematics('RigidBodyTree',robot,'ConstraintInputs',{'cartesian','position'});
boundingBox = constraintCartesianBounds('b5');
boundingBox.Bounds = [-Inf Inf; -Inf Inf; 0.01 Inf];
targetConstraint = constraintPositionTarget('b5');
targetConstraint.TargetPosition = pointA;
targetConstraint.PositionTolerance = 0.001;
q(1,:) = homeConfiguration(robot);

fps = 60;
trajTime = 1;
for k = 2:fps*trajTime
    %getPoint
    currPoint = pointA + (pointB-pointA)*k/fps/trajTime;
    %invkin
    targetConstraint.TargetPosition = currPoint;
    [q(k,:),solInfo] = invKinModel(q(k-1,:),boundingBox,targetConstraint);
    
end
framerate = 15;
r = rateControl(framerate);

hold on
for i = 1:10:size(q,1)
    
    config = q(i,:);
    show(robot, config, 'PreservePlot', false);
    waitfor(r);
end
hold off