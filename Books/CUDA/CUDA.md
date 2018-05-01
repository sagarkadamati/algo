## Install CUDA for Ubuntu

There is an [Linux installation guide](http://developer.download.nvidia.com/compute/cuda/7.5/Prod/docs/sidebar/CUDA_Installation_Guide_Linux.pdf). However, it is basically only those steps:

<ol>
<li><a href="https://developer.nvidia.com/cuda-downloads" rel="noreferrer">Download CUDA</a>: I used the 15.04 version and "runfile (local)". That is 1.1 GB.</li>
<li>Check the md5 sum: <code>md5sum cuda_7.5.18_linux.run</code>. Only continue if it is correct.</li>
<li>Remove any other installation (<code>sudo apt-get purge nvidia-cuda*</code> - if you want to install the drivers too, then <code>sudo apt-get purge nvidia-*</code>.)

<ol>
<li>If you want to install the display drivers<sup>(*)</sup>, logout from your GUI. Go to a terminal session (<kbd>ctrl</kbd>+<kbd>alt</kbd>+<kbd>F2</kbd>)</li>
<li>Stop lightdm: <code>sudo service lightdm stop</code></li>
<li>Create a file at <code>/etc/modprobe.d/blacklist-nouveau.conf</code> with the following contents:
<code>blacklist nouveau
options nouveau modeset=0</code></li>
<li>Then do: <code>sudo update-initramfs -u</code></li>
</ol></li>
<li><code>sudo sh cuda_7.5.18_linux.run --override</code>. Make sure that you say <code>y</code> for the symbolic link.

<ol>
<li>Start lightdm again: <code>sudo service lightdm start</code></li>
</ol></li>
<li>Follow the command-line prompts</li>
</ol>

<p>See also: <a href="https://www.pugetsystems.com/labs/hpc/NVIDIA-CUDA-with-Ubuntu-16-04-beta-on-a-laptop-if-you-just-cannot-wait-775/" rel="noreferrer">NVIDIA CUDA with Ubuntu 16.04 beta on a laptop (if you just cannot wait)</a></p>

<p><strong>Notes</strong>: Yes, there is the possibility to install it via <code>apt-get install cuda</code>. I strongly suggest not to use it, as it changes the paths and makes the installation of other tools more difficult.</p>

<p>You might also be interested in <a href="https://askubuntu.com/q/767269/10425">How can I install CuDNN on Ubuntu 16.04?</a>.</p>

<p>*: Don't install the display drivers with this script. They are old. Download the latest ones from <a href="http://www.nvidia.com/Download/index.aspx" rel="noreferrer">http://www.nvidia.com/Download/index.aspx</a></p>

<h2>Verify CUDA installation</h2>

<p>The following command shows the current CUDA version (last line):</p>

```
$ nvcc --version
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2016 NVIDIA Corporation
Built on Sun_Sep__4_22:14:01_CDT_2016
Cuda compilation tools, release 8.0, V8.0.44
```

The following command shows your driver version and how much GPU memory you have:

```
$ nvidia-smi
Fri Jan 20 12:19:04 2017       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 367.57                 Driver Version: 367.57                    |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  GeForce 940MX       Off  | 0000:02:00.0     Off |                  N/A |
| N/A   75C    P0    N/A /  N/A |   1981MiB /  2002MiB |     98%      Default |
+-------------------------------+----------------------+----------------------+

+-----------------------------------------------------------------------------+
| Processes:                                                       GPU Memory |
|  GPU       PID  Type  Process name                               Usage      |
|=============================================================================|
|    0      1156    G   /usr/lib/xorg/Xorg                             246MiB |
|    0      3198    G   ...m,SecurityWarningIconUpdate&lt;SecurityWarni   222MiB |
|    0      6645    C   python                                        1510MiB |
+-----------------------------------------------------------------------------+
````

<p>See also: <a href="https://stackoverflow.com/a/36978616/562769">Verify CuDNN installation</a></p>

<h2>Help! The new driver does not work!</h2>

<p>Don't panic. Even if you can't see anything on your computer, the following steps should get you back to the state before:</p>

<ol>
<li>Press <kbd>shift</kbd> while startup</li>
<li>Go into a root shell</li>
<li>Make it writable by <code>mount -o remount,rw /</code> (<code>-</code> is <code>?</code> and <code>/</code> is <code>-</code> in the american layout)</li>
<li><code>sh cuda_7.5.18_linux.run --uninstall</code></li>
<li><code>sudo apt-get install nvidia-361 nvidia-common nvidia-prime nvidia-settings</code></li>
</ol>

<h2>Graphic drivers</h2>

<p>Installing the graphic drivers is a bit tricky. This has to be done without graphics support.</p>

<ol>
<li>Logout from your current X session.</li>
<li><kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>F4</kbd> (you can switch back with <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>F7</kbd>)</li>
<li>You should remove all other drivers before.

<ol>
<li>Search them via <code>dpkg -l | grep -i nvidia</code></li>
<li>Remove them via <code>sudo apt-get remove --purge nvidia-WHATEVER</code></li>
</ol></li>
<li>Stop lightdm via <code>sudo service lightdm stop</code></li>
<li>You might need to <code>reboot</code> your pc / blacklist the nouveau driver (<a href="http://linuxwelt.blogspot.de/2014/08/losung-error-nouveau-kernel-driver-is.html" rel="noreferrer">German tutorial</a>)</li>
</ol>

</div>
    <div class="grid mb0 fw-wrap ai-start jc-end gs8 gsy">
    <div class="grid--cell mr16" style="flex: 1 1 100px;">
<div class="post-menu"><a href="/a/799185" title="short permalink to this answer" class="short-link" id="link-post-799185">share</a><span class="lsep">|</span><a href="/posts/799185/edit" class="suggest-edit-post" title="">improve this answer</a></div>                    </div>
    <div class="post-signature grid--cell fl0">
<div class="user-info user-hover">
    <div class="user-action-time">
        <a href="/posts/799185/revisions" title="show all edits to this post">edited <span title="2017-05-23 12:39:50Z" class="relativetime">May 23 '17 at 12:39</span></a>
    </div>
    <div class="user-gravatar32">
        <a href="/users/-1/community"><div class="gravatar-wrapper-32"><img src="https://www.gravatar.com/avatar/a007be5a61f6aa8f3e85ae2fc18dd66e?s=32&amp;d=identicon&amp;r=PG" alt="" width="32" height="32"></div></a>
    </div>
    <div class="user-details">
        <a href="/users/-1/community">Community</a><span class="mod-flair" title="moderator">&#9830;</span>
        <div class="-flair">
            <span class="reputation-score" title="reputation score " dir="ltr">1</span>
        </div>
    </div>
</div>
</div>








----------------------


<h2>Install CUDA for Ubuntu</h2>

<p>There is an <a href="http://developer.download.nvidia.com/compute/cuda/7.5/Prod/docs/sidebar/CUDA_Installation_Guide_Linux.pdf" rel="noreferrer">Linux installation guide</a>. However, it is basically only those steps:</p>

<ol>
<li><a href="https://developer.nvidia.com/cuda-downloads" rel="noreferrer">Download CUDA</a>: I used the 15.04 version and "runfile (local)". That is 1.1 GB.</li>
<li>Check the md5 sum: <code>md5sum cuda_7.5.18_linux.run</code>. Only continue if it is correct.</li>
<li>Remove any other installation (<code>sudo apt-get purge nvidia-cuda*</code> - if you want to install the drivers too, then <code>sudo apt-get purge nvidia-*</code>.)

<ol>
<li>If you want to install the display drivers<sup>(*)</sup>, logout from your GUI. Go to a terminal session (<kbd>ctrl</kbd>+<kbd>alt</kbd>+<kbd>F2</kbd>)</li>
<li>Stop lightdm: <code>sudo service lightdm stop</code></li>
<li>Create a file at <code>/etc/modprobe.d/blacklist-nouveau.conf</code> with the following contents:
<code>blacklist nouveau
options nouveau modeset=0</code></li>
<li>Then do: <code>sudo update-initramfs -u</code></li>
</ol></li>
<li><code>sudo sh cuda_7.5.18_linux.run --override</code>. Make sure that you say <code>y</code> for the symbolic link.

<ol>
<li>Start lightdm again: <code>sudo service lightdm start</code></li>
</ol></li>
<li>Follow the command-line prompts</li>
</ol>

<p>See also: <a href="https://www.pugetsystems.com/labs/hpc/NVIDIA-CUDA-with-Ubuntu-16-04-beta-on-a-laptop-if-you-just-cannot-wait-775/" rel="noreferrer">NVIDIA CUDA with Ubuntu 16.04 beta on a laptop (if you just cannot wait)</a></p>

<p><strong>Notes</strong>: Yes, there is the possibility to install it via <code>apt-get install cuda</code>. I strongly suggest not to use it, as it changes the paths and makes the installation of other tools more difficult.</p>

<p>You might also be interested in <a href="https://askubuntu.com/q/767269/10425">How can I install CuDNN on Ubuntu 16.04?</a>.</p>

<p>*: Don't install the display drivers with this script. They are old. Download the latest ones from <a href="http://www.nvidia.com/Download/index.aspx" rel="noreferrer">http://www.nvidia.com/Download/index.aspx</a></p>

<h2>Verify CUDA installation</h2>

<p>The following command shows the current CUDA version (last line):</p>

<pre><code>$ nvcc --version
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2016 NVIDIA Corporation
Built on Sun_Sep__4_22:14:01_CDT_2016
Cuda compilation tools, release 8.0, V8.0.44
</code></pre>

<p>The following command shows your driver version and how much GPU memory you have:</p>

<pre><code>$ nvidia-smi
Fri Jan 20 12:19:04 2017       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 367.57                 Driver Version: 367.57                    |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  GeForce 940MX       Off  | 0000:02:00.0     Off |                  N/A |
| N/A   75C    P0    N/A /  N/A |   1981MiB /  2002MiB |     98%      Default |
+-------------------------------+----------------------+----------------------+

+-----------------------------------------------------------------------------+
| Processes:                                                       GPU Memory |
|  GPU       PID  Type  Process name                               Usage      |
|=============================================================================|
|    0      1156    G   /usr/lib/xorg/Xorg                             246MiB |
|    0      3198    G   ...m,SecurityWarningIconUpdate&lt;SecurityWarni   222MiB |
|    0      6645    C   python                                        1510MiB |
+-----------------------------------------------------------------------------+
</code></pre>

<p>See also: <a href="https://stackoverflow.com/a/36978616/562769">Verify CuDNN installation</a></p>

<h2>Help! The new driver does not work!</h2>

<p>Don't panic. Even if you can't see anything on your computer, the following steps should get you back to the state before:</p>

<ol>
<li>Press <kbd>shift</kbd> while startup</li>
<li>Go into a root shell</li>
<li>Make it writable by <code>mount -o remount,rw /</code> (<code>-</code> is <code>?</code> and <code>/</code> is <code>-</code> in the american layout)</li>
<li><code>sh cuda_7.5.18_linux.run --uninstall</code></li>
<li><code>sudo apt-get install nvidia-361 nvidia-common nvidia-prime nvidia-settings</code></li>
</ol>

<h2>Graphic drivers</h2>

<p>Installing the graphic drivers is a bit tricky. This has to be done without graphics support.</p>

<ol>
<li>Logout from your current X session.</li>
<li><kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>F4</kbd> (you can switch back with <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>F7</kbd>)</li>
<li>You should remove all other drivers before.

<ol>
<li>Search them via <code>dpkg -l | grep -i nvidia</code></li>
<li>Remove them via <code>sudo apt-get remove --purge nvidia-WHATEVER</code></li>
</ol></li>
<li>Stop lightdm via <code>sudo service lightdm stop</code></li>
<li>You might need to <code>reboot</code> your pc / blacklist the nouveau driver (<a href="http://linuxwelt.blogspot.de/2014/08/losung-error-nouveau-kernel-driver-is.html" rel="noreferrer">German tutorial</a>)</li>
</ol>

</div>
    <div class="grid mb0 fw-wrap ai-start jc-end gs8 gsy">
    <div class="grid--cell mr16" style="flex: 1 1 100px;">
<div class="post-menu"><a href="/a/799185" title="short permalink to this answer" class="short-link" id="link-post-799185">share</a><span class="lsep">|</span><a href="/posts/799185/edit" class="suggest-edit-post" title="">improve this answer</a></div>                    </div>
    <div class="post-signature grid--cell fl0">
<div class="user-info user-hover">
    <div class="user-action-time">
        <a href="/posts/799185/revisions" title="show all edits to this post">edited <span title="2017-05-23 12:39:50Z" class="relativetime">May 23 '17 at 12:39</span></a>
    </div>
    <div class="user-gravatar32">
        <a href="/users/-1/community"><div class="gravatar-wrapper-32"><img src="https://www.gravatar.com/avatar/a007be5a61f6aa8f3e85ae2fc18dd66e?s=32&amp;d=identicon&amp;r=PG" alt="" width="32" height="32"></div></a>
    </div>
    <div class="user-details">
        <a href="/users/-1/community">Community</a><span class="mod-flair" title="moderator">&#9830;</span>
        <div class="-flair">
            <span class="reputation-score" title="reputation score " dir="ltr">1</span>
        </div>
    </div>
</div>
</div>