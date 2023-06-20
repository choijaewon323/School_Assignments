package calendar;

import java.awt.Color;
import java.util.Calendar;

import javax.swing.JButton;

import execution.MyGUIProject;

public class MyCalendar {
	
	private JButton[] buttons;
	private Calendar calendar = Calendar.getInstance();
	private int year;
	private int month;
	
	public MyCalendar() {
		year = calendar.get(Calendar.YEAR);
		month = calendar.get(Calendar.MONTH) + 1;
	}
	
	public void setButtons(JButton[] buttons) {
		this.buttons = buttons;
	}
	
	// 0000/00
	public String getDay() {
		return year + "/" + month;
	}
	
	public int getYear() {
		return year;
	}
	
	public int getMonth() {
		return month;
	}
	
	public void setCalendar() {
		calendar.set(year, month - 1, 1);
		
		// sunday : 1, monday : 2
		int firstDay = calendar.get(Calendar.DAY_OF_WEEK);
		firstDay--;
		
		for (int i = 0; i < buttons.length; i++) {
			buttons[i].setEnabled(false);
			buttons[i].setBackground(Color.WHITE);
		}
		
		for (int i = 1; i <= calendar.getActualMaximum(calendar.DATE); i++) {
			buttons[firstDay + i - 1].setEnabled(true);
			
			if (MyGUIProject.memos[year][month][i] == null) {
				buttons[firstDay + i - 1].setForeground(Color.BLACK);
			} else {
				buttons[firstDay + i - 1].setForeground(Color.RED);
			}
			
			buttons[firstDay + i - 1].setText(String.valueOf(i));
		}
	}
	
	public void renewal(boolean prev) {
		
		if (prev == true && month == 1 && year == 1) {
			return;
		}
		
		if (prev == false && month == 12 && year == 3000) {
			return;
		}
		
		for (int i = 0; i < buttons.length; i++) {
			buttons[i].setText("");
		}
		
		if (prev == true) {
			if (month == 1) {
				year--;
				month = 12;
			} else {
				month--;
			}
		} else {
			if (month == 12) {
				year++;
				month = 1;
			} else {
				month++;
			}
		}
		
		setCalendar();
	}
}













