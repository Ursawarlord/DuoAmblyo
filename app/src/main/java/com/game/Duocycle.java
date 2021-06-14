package com.game;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;
import android.widget.Toast;

import com.android.MemoryManager;
import com.duocycle.R;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

public class Duocycle extends Cocos2dxActivity {

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
	}

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	}



	@Override
	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		glSurfaceView.setEGLConfigChooser(8, 8, 8, 0, 0, 0);

		return glSurfaceView;
	}

	static {
		System.loadLibrary("player");
	}

	@Override
	protected void onResume() {
		super.onResume();
		MemoryManager.onResume();
	}

	@Override
	protected void onStart() {
		super.onStart();
		MemoryManager.onStart();
	}

	@Override
	protected void onStop() {
		super.onStop();
		MemoryManager.onStop();
	}

	@Override
	protected void onDestroy() {
		MemoryManager.onDestroy();
		super.onDestroy();
	}

	@Override
	public void onBackPressed() {
		MemoryManager.onBackPressed();
		exitConfirmation(this);
	}

	private void exitConfirmation(final Activity activity) {

		AlertDialog.Builder alertDlg = new AlertDialog.Builder(activity);
		alertDlg.setMessage("Do you Want Exit ?");
		alertDlg.setCancelable(false);

		alertDlg.setNegativeButton("Yes", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				activity.finish();
			}
		});

		alertDlg.setNeutralButton("No", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
			}
		});

		alertDlg.create().show();
	}

	@Override
	public void onNativeInit() {

	}
}
