Summary: Icarus Verilog
Name: verilog
Version: 0.6.20020915
Release: 0
Copyright: GPL
Group: Applications/Engineering
Source: ftp://icarus.com/pub/eda/verilog/snapshots/verilog-20020915.tar.gz
URL: http://www.icarus.com/eda/verilog/index.html
Packager: Stephen Williams <steve@icarus.com>

BuildRoot: /tmp/ivl

# This provides tag allows me to use a more specific name for things
# that actually depend on me, Icarus Verilog.
Provides: iverilog

%description
Icarus Verilog is a Verilog compiler that generates a variety of
engineering formats, including simulation. It strives to be true
to the IEEE-1364 standard.

%prep
%setup -n verilog-20020915

%build
./configure --prefix=/usr
make CXXFLAGS=-O

%install
make prefix=$RPM_BUILD_ROOT/usr install

%files

%attr(-,root,root) %doc COPYING README.txt BUGS.txt QUICK_START.txt ieee1364-notes.txt mingw.txt netlist.txt t-dll.txt vpi.txt xnf.txt tgt-fpga/fpga.txt xilinx-hint.txt
%attr(-,root,root) %doc examples/*

%attr(-,root,root) /usr/man/man1/iverilog.1.gz
%attr(-,root,root) /usr/man/man1/iverilog-vpi.1.gz
%attr(-,root,root) /usr/man/man1/vvp.1.gz

%attr(-,root,root) /usr/bin/iverilog
%attr(-,root,root) /usr/bin/iverilog-vpi
%attr(-,root,root) /usr/bin/vvp
%attr(-,root,root) /usr/lib/ivl/ivl
%attr(-,root,root) /usr/lib/ivl/ivlpp
%attr(-,root,root) /usr/lib/ivl/system.vpi
%attr(-,root,root) /usr/lib/ivl/null.tgt
%attr(-,root,root) /usr/lib/ivl/vvp.tgt
%attr(-,root,root) /usr/lib/ivl/fpga.tgt
%attr(-,root,root) /usr/lib/ivl/iverilog.conf
%attr(-,root,root) /usr/lib/libvpi.a
%attr(-,root,root) /usr/lib/libveriuser.a
%attr(-,root,root) /usr/include/ivl_target.h
%attr(-,root,root) /usr/include/vpi_user.h
%attr(-,root,root) /usr/include/acc_user.h
%attr(-,root,root) /usr/include/veriuser.h
