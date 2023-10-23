%
% Finite different tester
%
% Scott Collis
% 10-30-2011
%
% Note:  boundary effects are ignored for now
%
staggered = 1;
order = 8;
drp = 0;
halo = order/2;

% setup finite difference stencils
if staggered == 1
    if order == 4
        % FDM Fourth order (staggered)
        c1 =  9.0 / 8.0;
        c2 = -1.0 / 24.0;
        c3 =  0.0;
        c4 =  0.0;
    elseif order == 6
        % FDM Sixth order (staggered)
        c1 =  75.0 /  64.0;
        c2 = -25.0 / 384.0;
        c3 =   3.0 / 640.0;
        c4 =   0.0;
    else
        % FDM eighth-order (staggered)
        c1 = 1125.0 / 1024.0;
        c2 = -245.0 / 3072.0;
        c3 =   49.0 / 5120.0;
        c4 =   -5.0 / 7168.0;
    end
else
    if order == 6    
        % Sixth-order (non-staggered)
        c1 = 45.0 / 60.0;
        c2 = -9.0 / 60.0;
        c3 =  1.0 / 60.0;
        c4 =  0.0;
    else
        if drp == 1
            % Dispresion-relation preserving (non-staggered)
            c1 =  0.841570125482;
            c2 = -0.244678931765;
            c3 =  0.059463584768;
            c4 = -0.007650904064;
        else
            % Eighth-order (non-staggered)
            c1 =  672.0 / 840.0;
            c2 = -168.0 / 840.0;
            c3 =   32.0 / 840.0;
            c4 =   -3.0 / 840.0;
        end
    end
end

Lx = 2.0*pi;
Nx = 50;
dx = 2.0*pi/Nx;
dxi = 1.0/dx;
x = 0: dx: Lx;
f = sin(x);
Nxp = size(x,2);
df = zeros(size(f));
dfdx = cos(x);
if staggered == 1
    shift = 2*pi/50/2;
    for i=5:Nxp-4
        df(i) = ((c4*(f(i+4) - f(i-3)) + ...
                  c3*(f(i+3) - f(i-2)) + ...
                  c2*(f(i+2) - f(i-1)) + ...
    	          c1*(f(i+1) - f(i  ))))/dx;
    end
else
    shift = 0;
    for i=5:Nxp-4
        df(i) = ((c4*(f(i+4) - f(i-4)) + ...
                  c3*(f(i+3) - f(i-3)) + ...
                  c2*(f(i+2) - f(i-2)) + ...
    	          c1*(f(i+1) - f(i-1))))/dx;
    end
end
clf;
plot(x,f);
hold on;
% do not plot the boundary region right now
plot(x(5:Nx-5)+shift,df(5:Nx-5),'-r');
plot(x,dfdx,'-k');
hold off;