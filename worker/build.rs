use std::env;
use std::process::Command;

fn main() {
    if std::env::var("DOCS_RS").is_ok() {
        // Skip everything when building docs on docs.rs
        return;
    }

    // Add C++ std lib
    #[cfg(target_os = "linux")]
    {
        let path = Command::new(env::var("c++").unwrap_or_else(|_| "c++".to_string()))
            .arg("--print-file-name=libstdc++.a")
            .output()
            .expect("Failed to start")
            .stdout;
        println!(
            "cargo:rustc-link-search=native={}",
            String::from_utf8_lossy(&path)
                .trim()
                .strip_suffix("libstdc++.a")
                .expect("Failed to strip suffix"),
        );
        println!("cargo:rustc-link-lib=static=stdc++");
    }
    #[cfg(any(
        target_os = "freebsd",
        target_os = "dragonfly",
        target_os = "openbsd",
        target_os = "netbsd"
    ))]
    {
        let path = Command::new(env::var("c++").unwrap_or_else(|_| "c++".to_string()))
            .arg("--print-file-name=libc++.a")
            .output()
            .expect("Failed to start")
            .stdout;
        println!(
            "cargo:rustc-link-search=native={}",
            String::from_utf8_lossy(&path)
                .trim()
                .strip_suffix("libc++.a")
                .expect("Failed to strip suffix"),
        );
        println!("cargo:rustc-link-lib=static=c++");
    }
    #[cfg(target_os = "macos")]
    {
        panic!("Building on macOS is not currently supported");
        // TODO: The issue here is `libc++.a` that is not shipped with macOS's `c++` it seems
    }
    #[cfg(target_os = "windows")]
    {
        panic!("Building on Windows is not currently supported");
        // TODO: Didn't bother, feel free to PR
    }

    let current_dir = std::env::current_dir()
        .unwrap()
        .into_os_string()
        .into_string()
        .unwrap();
    let out_dir = env::var("OUT_DIR").unwrap();

    // The build here is a bit awkward since we can't just specify custom target directory as
    // openssl will fail to build with `make[1]: /bin/sh: Argument list too long` due to large
    // number of files. So instead we build in place, copy files to out directory and then clean
    // after ourselves
    {
        // Build
        if !Command::new("make")
            .arg("libmediasoup-worker")
            .spawn()
            .expect("Failed to start")
            .wait()
            .expect("Wasn't running")
            .success()
        {
            panic!("Failed to build libmediasoup-worker")
        }

        for file in &[
            "libnetstring.a",
            "libuv.a",
            "libopenssl.a",
            "libsrtp.a",
            "libusrsctp.a",
            "libwebrtc.a",
            "libmediasoup-worker.a",
            "libabseil.a",
            #[cfg(windows)]
            "libgetopt.a",
        ] {
            std::fs::copy(
                format!("{}/out/Release/{}", current_dir, file),
                format!("{}/{}", out_dir, file),
            )
            .unwrap_or_else(|_| {
                panic!(
                    "Failed to copy static library from {}/out/Release/{} to {}/{}",
                    current_dir, file, out_dir, file
                )
            });
        }

        if env::var("KEEP_BUILD_ARTIFACTS") != Ok("1".to_string()) {
            // Clean
            if !Command::new("make")
                .arg("clean-all")
                .spawn()
                .expect("Failed to start")
                .wait()
                .expect("Wasn't running")
                .success()
            {
                panic!("Failed to clean libmediasoup-worker")
            }
        }
    }

    println!("cargo:rustc-link-lib=static=netstring");
    println!("cargo:rustc-link-lib=static=uv");
    println!("cargo:rustc-link-lib=static=openssl");
    println!("cargo:rustc-link-lib=static=srtp");
    println!("cargo:rustc-link-lib=static=usrsctp");
    println!("cargo:rustc-link-lib=static=webrtc");
    println!("cargo:rustc-link-lib=static=mediasoup-worker");
    println!("cargo:rustc-link-lib=static=abseil");
    #[cfg(windows)]
    println!("cargo:rustc-link-lib=static=getopt");
    println!("cargo:rustc-link-search=native={}", out_dir);
}
