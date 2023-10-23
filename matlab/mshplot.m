function mshplot(grid)
% MSHPLOT Plot DGM mesh
%
%   MSHPLOT(GRID) Plot DGM mesh where GRID is the output of
%   MSHREAD.
%
% See also MSHREAD, TECPLOT

if (grid.dim ~= 2), error('Only 2d plotting for now'); end;

% Store coordinates from all elements
for e=1:grid.nelem
  X(:,e) = grid.element(e).coordinates(:,1);
  Y(:,e) = grid.element(e).coordinates(:,2);
end

% Complete the polygon
X = [X; X(1,:)]; Y = [Y; Y(1,:)];
  
% Plot the msh
line(X, Y, 'Color', 0.6*[1 1 1]);
axis image;
