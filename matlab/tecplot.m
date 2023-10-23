function tecplot(varargin)
% TECPLOT Plot DGM solution
%
%   TECPLOT(DATA, VARIABLE) Displays the DGM exported solution,
%   DATA, as read in by TECREAD, for the unknown, VARIABLE.
%   VARIABLE can be a string input, such as 'Sw', or the index
%   into the DATA.FIELDNAME cell array.
%
%   TECPLOT(DATA, VARIABLE, PLOTFUNCTION) uses the Matlab
%   plotting function specified by the string argument, 
%   PLOTFUNCTION.  Valid options are 'pcolor'/'2d' for filled
%   contour plots, 'surf' for 3d surface plots and 'mesh' for 
%   3d wire plots.
%
%   TECPLOT(AX,...) Places the plot into the axis specified 
%   by AX.
%
% See also TECREAD, MSHPLOT

% Parse input arguments
[cax,args] = axescheck(varargin{:});

if (length(args) < 2), 
  error('Need to specify at least data structure and plotting variable');
end

% Input data
data = args{1};

% Plotting field
variable = args{2};

% Check plotting string
plotfun = '2d';
if (length(args) >= 3)
  plotfun = args{3};
end
if ~ischar(plotfun),
  error('PLOTFUN must be string input');
end
switch(lower(plotfun))
 case {'pcolor','2d','contour','contourf','surf','3d','surf3d','mesh','mesh3d','quiver'}
 otherwise
  error('PLOTFUN not understood');
end

if (length(args) > 3),
  error(sprintf('Unknown argument after %s',plotfun));
end

% Get plotting data
if ischar(variable)
  vind = 0;
  for i=1:length(data.fieldname)
    if strcmp(data.fieldname{i}, variable), vind=i; end;
  end
  if (vind == 0), error('Unknown variable name'); end;
else
  vind = variable;
end
% Get x and y field indices
for i=1:length(data.fieldname)
  if strcmp(data.fieldname{i}, 'x'), 
    xind = i; 
  elseif strcmp(data.fieldname{i}, 'y'), 
    yind = i; 
  end
end

% Plot the data
if (data.grid.dim == 2)
  if isempty(cax), figure; cax = gca; end;
  axis(cax); hold on;
  for e=1:data.grid.nelem
    switch(lower(plotfun))
     case {'pcolor','2d','contour','contourf'}
      pcolor(cax,data.fielddata{e,xind}, data.fielddata{e,yind}, data.fielddata{e,vind});
     case {'surf','3d','surf3d'}
      surf(cax,data.fielddata{e,xind}, data.fielddata{e,yind}, data.fielddata{e,vind});
     case {'mesh','mesh3d'}
      mesh(cax,data.fielddata{e,xind}, data.fielddata{e,yind}, data.fielddata{e,vind});
     case {'quiver'}
      quiver(data.fielddata{e,xind}, data.fielddata{e,yind}, data.fielddata{e,vind}, data.fielddata{e,vind+1});
    end
  end

  colormap(jet(4^8));
  xlabel('x'); ylabel('y'); colorbar;

  switch(lower(plotfun))
   case {'pcolor','2d','contour','contourf'}
    shading interp; view(2);
   case {'surf','3d','surf3d'}
    shading interp; view(3);
   case {'mesh','mesh3d'}
    view(3); 
  end
  
end
axis image; drawnow;
