function data = tecread(fname, casename)
% TECREAD Read DGM export to Tecplot formatted output
%
%   DATA = TECREAD(FNAME, CASENAME) reads the .dat-file, FNAME,
%   as a DGM export to Tecplot formatted output for the DGM case,
%   CASENAME.  This assumes that the CASENAME.msh file is accessible.
%   The output is returned is the DATA structure.
%
% See also TECPLOT, MSHREAD

% Read the grid first
data.grid = mshread(casename);

% Set the dat file name
fname = strrep(fname, '.dat', '');
fname = [fname '.dat'];

% Open the file
if (exist(fname, 'file') == 0), error(['File, ' fname ' does not exist']); end;
fid = fopen(fname);

% Read title line
A = fgets(fid);

% 1d and multi-d have different output formats- doh!
if (data.grid.dim == 1)
  % Initialize the data
  nvar = 0;
  data.fieldname = {};
  
  % Read the next line
  A = fgets(fid);

  while 1
    % Loop ends when A is empty
    if (A==-1), break; end;
    
    % Loop starts with variable name
    [ivar varnames] = getvarnames(A);

    % Save variable names and initialize data
    data.fieldname = [data.fieldname varnames];
    for i=1:ivar, data.fielddata{nvar+i} = []; end;
    
    % Read zone header line
    A = fgets(fid);
    
    % Read the next line
    while 1
      A = fgets(fid);
      if (A==-1 | ~isempty(strfind(A,'VARIABLE'))), break; end;
      tmpdata = sscanf(A, '%f', ivar);
      for i=1:ivar, 
        data.fielddata{nvar+i} = [data.fielddata{nvar+i}; tmpdata(i)]; 
      end;
    end

    % Increment variable counter
    nvar = nvar + ivar;
  
  end
  
else % multi-d format
  
  % Read variables line
  A = fgets(fid);
  [nvar data.fieldname] = getvarnames(A);
  
  % Read in variable data
  data.fielddata = cell(data.grid.nelem,nvar);
  for e=1:data.grid.nelem
    
    % Element header line
    A = fgets(fid);
    
    % Read in number of subdivisions
    while 1
      % Tokenize by the comma
      [tok,A]=strtok(A,',');
      if isempty(tok), break; end;
      
      % Tokenize by =, first token is variable name
      [opt,tok]=strtok(tok,'=');
      
      % Second token is variable value
      [num,jnk]=strtok(tok,'=');
      
      % Store subdivision numbers
      if strcmp(strtrim(opt),'I'), 
        ni=strread(num,'%d'); 
      elseif strcmp(strtrim(opt),'J'), 
        nj=strread(num,'%d'); 
        break;
      end;
    end
    
    % Read in variable data
    for i=1:nvar
      A= fscanf(fid, '%f', [nj ni]);
      data.fielddata{e,i} = A';
    end
    A=fgets(fid);
  end
end

% Close the file
fclose(fid);

%--------------------------------------------%
function [nvar varnames]=getvarnames(linestr)
linestr = strrep(linestr, 'VARIABLES=', '');

% Read in variable names
nvar = 0;
while 1
  % Read next variable name
  [tok, linestr] = strtok(linestr);
  
  % Quit if we have read all the tokens
  if isempty(tok), break; end;
  
  % Increment variable counter
  nvar = nvar + 1;
  
  % Store variable name
  varnames{nvar} = strrep(tok,'"','');
end
return;
%--------------------------------------------%
