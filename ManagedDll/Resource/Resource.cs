﻿using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public abstract class Resource : NativeClass {
        public string FileName { get; set; }

        public Resource() {
        }

        public Resource(IntPtr ptr) : base(ptr) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Status Resource_load(IntPtr _this, IntPtr manager, string fileName);

        public virtual Status Load(ResourceManager resourceManager, string fileName) {
            return Resource_load(NativePtr, resourceManager.NativePtr, fileName);
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Status Resource_save(IntPtr _this, IntPtr manager, string fileName);

        public virtual Status Save(ResourceManager resourceManager, string fileName) {
            return Resource_save(NativePtr, resourceManager.NativePtr, fileName);
        }
    }
}