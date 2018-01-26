# Hyrax, Hyrax-unopt, BCCGP, Bulletproofs, ZKBoo #

This directory includes implementations of five different zk proof systems
for arithmetic circuit satisfiability. (We do not include the Ligero source
because its authors have not released it to the public.)

This readme gives instructions for building and running all of this code.

# Installing libraries #

These instructions are known to work under Debian Stretch and Debian Buster.
They will probably work on recent Ubuntu distributions, too.

## Running on EC2 ##

If you're going to run on EC2, head over to the [Debian
Wiki](https://wiki.debian.org/Cloud/AmazonEC2Image/Stretch) and find the
identifier for the Debian 9.x AMI. As of the time of this writing, if you're
running in Oregon (us-west-2), you would use `ami-a0f247d8`.

We strongly recommend that you run on a c3.4xlarge or c3.8xlarge instance, and
that you attach the instance store (local SSDs) at launch. Note that if you're
running on an instance that doesn't have local SSDs (e.g., c4 or c5 instances)
you won't need to prepare the instance store as listed below.

Once you've started up your machine and logged in as admin, do a quick

    sudo apt-get -y update
    sudo apt-get -y dist-upgrade

## Installing packages ##

You will need (most of) the following packages:

    apt-get -y install htop screen mdadm xfsprogs g++ build-essential \
               pypy python-cffi python-dev libssl-dev libgmp-dev automake \
               pkg-config libtool libtool-bin git tig links parted parallel

## Preparing the instance store (EC2 only) ##

If you're on an instance with local SSDs, the following is probably useful.

First, we're going to make a RAID-0 block device:

    sudo su
    umount /dev/xvdca /dev/xvdcb
    echo yes | mdadm --create /dev/md0 --level 0 -n 2 /dev/xvdca /dev/xvdcb

Now we're going to partition it into a swap and a data partition:

    parted --script /dev/md0 mklabel gpt \
                             mkpart primary linux-swap 1MiB 256GiB \
                             mkpart primary xfs 256GiB 100%
    partprobe /dev/md0
    sleep 2

Finally, we're going to format and mount the new partitions:

    mkswap /dev/md0p1
    swapon /dev/md0p1
    mkdir /ext
    mkfs -t xfs -f /dev/md0p2
    mount /dev/md0p2 /ext
    chown admin.admin /ext
    exit

Great! Now we've got 256GiB of swap and a bunch of fast storage attached at
/ext. Note that if your instance's SSDs aren't big enough, you'll have to
tune the parted arguments above.

## Build NTL ##

To run the BCCGP code, you'll need to have NTL 10.x installed. Debian 9.x
doesn't package a recent enough version, so we'll have to build from source
instead.

First, make a directory, link it to your homedir (you'll need this later),
and unpack the source.

    mkdir -p /ext/toolchains/src
    ln -s /ext/toolchains $HOME/toolchains
    cd /ext/toolchains/src
    wget http://shoup.net/ntl/ntl-10.5.0.tar.gz
    tar xzvf ntl-10.5.0.tar.gz
    cd ntl-10.5.0/src

Now we're going to configure and build NTL. The following options are known to work.

    ./configure DEF_PREFIX=/usr PREFIX=/ext/toolchains SHARED=on \
                NTL_THREAD_BOOST=on NTL_STD_CXX14=on
    make -j
    make install

The above build will take a while because it'll run some tuning scripts. Give
it five minutes or so.

## Clone and build the source ##

Now we grab Hyrax's source, then build and test it:

    cd /ext
    git clone https://github.com/hyraxOakland2018/hyrax
    cd /ext/hyrax/src/bccgp
    make -j
    cd /ext/hyrax/src/fennel
    make -j
    python libfenneltests 10

## Get public parameters (a.k.a. random group elements) ##

We have generated lots of random group elements for use with the largest
test cases. In particular, for the largest computations it can handle on a
machine with 60 GiB of RAM, Bulletproofs requires 2^24 random group elements.
See the file `src/miracl/lib/m191big_multi_url` for three URLs.

(Tip: navigate to the URL in your browser, then click the "Download" button.
Point the command-line browser `links` at the resulting URL.)

If you want to generate some for yourself, consult the Sage scripts in
`src/miracl/lib`. To run these scripts you will need to install Sage; on
Debian-like systems, you should use

    apt-get install sagemath

(warning: this will install a lot of packages and probably take a long time!)

## Building ZKBoo ##

See README.md in the zkboo subdirectory.

# Running experiments #

Our experiment scripts are located in src/pws/experiments.

# License #

(C) 2018 Hyrax Authors --- ALL RIGHTS RESERVED
